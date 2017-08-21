#AlayaSDK iOS版接入说明(v1.0.1)**注1\*: 该静态库只能使用真机进行编译调试**  
**注2\*: 如果使用SDK录制期间还使用了内置麦克风, 请将AVAudioSessionCategoryOptionAllowBluetooth这一配置项取消掉**
****## 0.接入准备### 0.1 将SDK包导入到工程里
在工程中添加 SabineSwissSDK.framework 包### 0.2 引入头文件在需要使用SDK 的类中引入 #import < SabineSwissSDK/SabineSwissSDK.h>, 并且把 该类的 .m 文件改为 .mm 格式### 0.3 加入对EAP协议的支持iAP协议是iOS设备访问以非标准蓝牙协议访问外部蓝牙设备的必须协议，需要在工程中开启方可使用。请在工程的 info.plist 中添加 "Supported external accessory protocols" 字段, 并添加一个 string 类型的 "com.sabinetek.iisrecorder" 的 item, 详见 demo 中的配置。##1. 初始化###1.1 将耳机与iPhone相连使用该SDK前，请先确保ALAYA已经与调试设备相连。  连接方法：  确保ALAYA处于关机、有电的情况下，长按开关键约5-7秒，至提示灯以蓝绿交替方式闪烁后，在手机上搜索Sabine_XXX蓝牙设备，点击以建立连接。###1.2 录音链接创建该功能是任何应用程序使用Alaya设备的必须步骤，通过以下流程实现：  实例化STDManager类, 创建单例:

```objecttive-C  
[STDManager sharedInstance]
```
    注册 STAccessoryConnectStateChangeNotification 通知, 监听蓝牙协议连接状态变化.  然后调用:

```objecttive-C  
- (BOOL)STD_Connect;
```
该方法的返回值表示是否正在连接的是Sabine Alaya.  
连接蓝牙协议(建议在app启动时调用 - (void)applicationDidBecomeActive:), 成功时会收到通知, 此时isConnect 字段为YES 表示连接成功.  
如果需要断开蓝牙协议, 则调用:  

```objecttive-C  - (void)STD_Disconnect;
```

 建议在app terminate时调用, 断开蓝牙协议##2. 录音数据收发开关作为一个蓝牙设备，当Alaya通过蓝牙通道向设备发送立体声音频数据的时候，需要经过采集、编码、降噪、蓝牙传输等多个步骤，而这些事务将显著增加Alaya的电量消耗。当Alaya一直处于音频数据发送状态时只能连续工作8小时，而如果仅仅是与手机建立蓝牙链接而不发送数据，则可以工作30小时。因此当应用程序的业务逻辑不需要音频的时候，建议停止Alaya的录音数据发送。###2.1开始获取录音数据 
#### (注*: 需收到STAccessoryConnectStateChangeNotification 通知后再调用下面的 start方法, 连接需要1-2s时间, 如果直接 start 可能在 delegate 回调中无法正常收到数据)打开Alaya的录音数据发送开关的方法为:  

```objecttive-C  - (BOOL)STDR_Start;
```
或

```objecttive-C  - (BOOL)STDR_StartWithDelegate:(id <STDManagerAudioStreamDelegate>)delegate;
```开始接收数据后, 数据可以在代理方法中获取到录音数据为PCM格式。位宽16Bit、采样率为48000Hz, 若编码成AAC格式其码率建议是128kbps  
接收到的数据通过代理方法 STD_PCMBuffer:didReceivePCMBytes:pcmByteSize: 获取;###2.2停止获取录音数据调用: 

```objecttive-C 
- (BOOL)STDR_Stop;
```
 结束PCM获取数据##3.耳机状态控制功能###3.1监听控制 (v0.50 后改为 NSInteger 类型, 取值范围 0 ~ 20)该功能可用于在录音数据开关打开的时候，正在录制的声音是否会在耳机中立刻播放。设置方法：

```objecttive-C  @property (nonatomic, assign) NSInteger monitor 
```

用于打开/关闭监听功能 (v0.31 后已改为默认是关闭状态, monitorOn == NO)

##4.Sabine 调试 Log开关
设置调试Log开关, 默认是个关闭的; 

```objecttive-C  
+ (void)setSabineLog:(BOOL)isOn; 
```

读取Log开关状态

```objecttive-C  
+ (BOOL)isSabineLogOn;
```
v0.27新增蓝牙设备crash log
##5.开放音频缓存区入口
```objecttive-C 
@property (nonatomic, strong, readonly)STCircularPCMBufferModel *pcmCircularBuffer;
```
###5.1增加接收数据状态接口
```objecttive-C 
@property (nonatomic, assign, readonly) BOOL isRecording;
``` 
##6.耳机采样率设置
```objecttive-C 
@property (nonatomic, assign) STDAudioSampleRate sampleRate;
```  
```objecttive-C 
typedef NS_ENUM(NSInteger, STDAudioSampleRate){
    STDAudioSampleRate48000,
    STDAudioSampleRate44100
};
```
目前只有两个枚举值可设置, 默认采样率是48000, 更改采样率设置必须要在 start 之前

##7.数据传输抖动控制
```objecttive-C 
@property (nonatomic, assign) BOOL jitterControlOn;
```  
默认值是NO, 开启后会让接收数据的回调间隔变平稳  

##8.连接到的 Sabine 设备类型
```objecttive-C 
typedef NS_ENUM(NSInteger, STDHardwardType) {
    STDHardwardTypeNone = 0,
    STDHardwardTypeAlayaSilver,
    STDHardwardTypeAlayaPro,
    STDHardwardTypeSMIC
};

@property (nonatomic, assign, readonly) STDHardwardType deviceType;
```  
##9.其它功能接口
```objecttive-C 
@property (nonatomic, assign) NSInteger ans; // 降噪等级 范围 0 ~ 20
@property (nonatomic, assign) NSInteger mixer; // 混音开关 范围 0 ~ 20
@property (nonatomic, assign) NSInteger reverb; // 混响开关(目前只对SMIC有效) 范围 0 ~ 20
@property (nonatomic, assign) BOOL agcOn;      // 自动增益控制开关, 默认为打开
@property (nonatomic, assign) NSInteger micGain; // mic 增益调节, 范围 0 ~ 20
```  

