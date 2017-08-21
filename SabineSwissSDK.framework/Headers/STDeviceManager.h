//
//  STDeviceManager.h
//  SabineBTSDK
//
//  Created by 赵鑫磊 on 16/7/1.
//  Copyright © 2016年 赵鑫磊. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT NSString * const kSDKVertion;
/*!
 * 蓝牙协议连接状态发生变化的通知
 */
FOUNDATION_EXPORT NSString * const STAccessoryConnectStateChangeNotification;
    /*
     * 蓝牙协议当前状态,Notification 中的 userInfo key, value 为 BOOL 类型 NSNumber 对象
     */
    FOUNDATION_EXPORT NSString * const STAccessoryConnectStateKey;
/*!
 * 蓝牙协议名
 */
FOUNDATION_EXPORT NSString * const kProtocoliAP2; // @"com.sabinetek.iisrecorder"


typedef NS_ENUM(NSInteger, STDAudioSampleRate) {
    STDAudioSampleRate48000 = 48000,
    STDAudioSampleRate44100 = 44100
};

typedef NS_ENUM(NSInteger, STDHardwardType) {
    STDHardwardTypeNone = 0,
    STDHardwardTypeAlayaSilver,
    STDHardwardTypeAlayaPro,
    STDHardwardTypeSMIC
};


@class STCircularPCMBufferModel;
@protocol STDManagerAudioStreamDelegate <NSObject>
@optional
/*!
 * 收到PCM数据后的回调, 每次从pcmBuffer 读取的数据应大于等于 pcmSize(3072) 否则, 未读取的数据会一直缓存下去, 直到pcmBuffer填满, 填满后新数据会覆盖最早的旧数据.
 * @params pcmBuffer 存储音频数据的缓冲区, 需调动 STCircularPCMBufferModel 类中的接口获取
 * @params pcm 刚接收到的PCM数据
 * @params pcmSize 刚接收到的PCM数据长度(sizeof(Byte) 3072)
 */
- (void)STD_PCMBuffer:(STCircularPCMBufferModel *)pcmBuffer didReceivePCMBytes:(Byte *)pcm pcmByteSize:(SInt32)pcmSize;
@end



@interface STDManager : NSObject

/*!
 * 与蓝牙录音协议的连接状态, 收到STAccessoryConnectStateChangeNotification 通知, 则表明该变量发生变化
 */
@property (nonatomic, assign, readonly) BOOL isConnect;
/*!
 * 表示当前是否获取音频数据中
 */
@property (nonatomic, assign, readonly) BOOL isRecording;

/*!
 * 开关监听 (即耳返) 注: v0.50 后改为 NSInteger 类型
 * 取值范围 0 ~ 20 (0 表示关闭, 默认设为关闭状态);
 */
@property (nonatomic, assign) NSInteger monitor;

/*!
 * 缓存蓝牙数据的Buffer 空间为80K, 最多缓存大约400ms数据
 */
@property (nonatomic, strong, readonly)STCircularPCMBufferModel *pcmCircularBuffer;

/*!
 * 设置采样率, 只支持 44100 和 48000 默认是48000;
 * 必须在start 之前设置
 */
@property (nonatomic, assign) STDAudioSampleRate sampleRate;

/*!
 * 数据回调防抖动控制的开关, 默认是 NO 关闭着的
 * 如开启, 需在 start 之前设置
 */
@property (nonatomic, assign) BOOL jitterControlOn;

/*!
 * Sabine 连接的硬件设备类型
 */
@property (nonatomic, assign, readonly) STDHardwardType deviceType;

/*!
 * 降噪等级(0-3), 0表示关闭
 * ANS Value - 0, 1, 2, 3
 */
@property (nonatomic, assign) NSInteger ans;

/*!
 * 混音设置值, 0表示关闭
 * 取值范围 0 ~ 20
 */
@property (nonatomic, assign) NSInteger mixer;

/*!
 * 混响设置值, 0表示关闭
 * 取值范围 0 ~ 20
 */
@property (nonatomic, assign) NSInteger reverb;

/*!
 * 开关 自动增益控制 (Auto Gain Control), 默认为开启
 *
 */
@property (nonatomic, assign) BOOL agcOn;

/*!
 * mic 增益调节
 * 取值范围 0 ~ 20
 */
@property (nonatomic, assign) NSInteger micGain;

/*!
 * 固件版本号
 */
@property (nonatomic, strong, readonly) NSString *firmwareVersion;

@property (nonatomic, weak) id <STDManagerAudioStreamDelegate> delegate;
+ (instancetype)sharedInstance;

/*!
 * 连接蓝牙协议
 * @return YES 表示正在连接的是Sabine蓝牙设备
 */
- (BOOL)STD_Connect;

/*!
 * 断开蓝牙协议
 */
- (void)STD_Disconnect;

/*!
 * 开始获取数据
 * @return YES 表示成功, NO 表示失败(可能是蓝牙未连接)
 */
- (BOOL)STDR_Start;
- (BOOL)STDR_StartWithDelegate:(id <STDManagerAudioStreamDelegate>)delegate;

/*!
 * 结束获取数据
 * @reture YES 表示成功, NO 表示失败(可能是蓝牙未连接);
 */
- (BOOL)STDR_Stop;

/*!
 * 设置调试log开关, 默认是关闭的
 */
+ (void)setSabineLog:(BOOL)isOn;


+ (BOOL)isSabineLogOn;

@end
