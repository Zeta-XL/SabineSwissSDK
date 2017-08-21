//
//  STCircularPCMBufferModel.h
//  ExternalAccessorySample
//
//  Created by 赵鑫磊 on 16/3/22.
//  Copyright © 2016年 赵鑫磊. All rights reserved.
//

#import "STCircularBufferModel.h"

#import <AVFoundation/AVFoundation.h>





@class STCircularPCMBufferModel;
@protocol STCirculatPCMBufferDelegate <NSObject>
@optional

/*
 * ---------------------------------------------------------------------------------------------
 * 
 * ---------------------------------------------------------------------------------------------
 */

/*!
 * @discussion circularBuffer 收到数据后的回调方法, 该协议目前已由STDManger实现, 不必关注
 * @params circularBuff 存储音频数据的buffer
 * @params pcm 接收到的PCM数据
 * @params pcmSize 接收到的PCM数据长度(sizeof(Byte))
 */
- (void)circularBuffer:(STCircularPCMBufferModel *)circularBuff
    hasReceivePCMBytes:(Byte *)pcm
           pcmByteSize:(SInt32)pcmSize;


@end



@interface STCircularPCMBufferModel : STCircularBufferModel 
// 默认为2声道
@property (nonatomic, assign, readonly) SInt32 numOfChannels;
// 当前时间戳 (系统时钟对应的时间戳, 时间精度为纳秒)
@property (nonatomic, assign, readonly) CMTime currentTimeStamp;
// 当前时间戳 (自1970.1.1的时间戳, 时间精度为纳秒)
@property (nonatomic, assign, readonly) CMTime currentTimeStampSince1970;
@property (nonatomic, weak) id <STCirculatPCMBufferDelegate> delegate;

// 抖动缓冲控制的开关
@property (nonatomic, assign) BOOL jitterControlOn;

/*!
 * @discussion 此方法与代理方法 STD_PCMBuffer:didReceivePCMBytes:pcmByteSize:; 配合使用
 * @params byteLength 需要读取的数据长度(sizeof(Byte)) 一般为1024*2*numOfChannel
 * @return 需要读取的PCM数据, 如果读取的长度大于缓存中的长度则返回NULL
 *
 */
- (Byte *)readPCMByteWithLength:(SInt32)byteLength;

/*!
 * @discussion 此方法与代理方法 STD_PCMBuffer:didReceivePCMBytes:pcmByteSize:; 配合使用
 * @params bufferSize 需要读取的 AudioBuffer 中的大小, 一般为1024*2*numOfChannel
 * @return 根据 bufferSize 生成的AudioBufferList, 如果读取的长度大于缓存中的长度则返回NULL
 *
 */
- (AudioBufferList *)readAudioBufferListWithAudioBufferSize:(SInt32)bufferSize;


/*!
 * @discussion 此方法与代理方法 STD_PCMBuffer:didReceivePCMBytes:pcmByteSize:; 配合使用
 * @params pcmByteLength 需要读取的 pcm 数据的Byte大小
 * @params parseBlock 根据pcmByteLength 生成SampleBufferRef, 若如果读取的长度大于缓存中的长度则block中的sampleBuffer为NULL,
 */
- (void)readAudioSampleButterWithPCMByteLength:(SInt32)pcmByteLength
                                    parseBlock:(void(^)(CMSampleBufferRef sampleBuffer))parseBlock;

/*!
 * @discussion 方法readPCMByteWithLength: 方法readAudioBufferListWithAudioBufferSize: 和方法readAudioSampleButterWithPCMByteLength:
 parseBlock: 都会自行调用此方法
 * @params byteLength 标记为已读的数据长度
 * @return YES/NO 标记是否成功, 如果 byteLength 超过缓存数据的大小, 返回 NO
 */
- (BOOL)markByteLengthAsRead:(SInt32)byteLength;

@end
