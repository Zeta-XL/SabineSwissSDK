//
//  STAudioStreamBasicFormat.h
//  SabineBTSDK
//
//  Created by 赵鑫磊 on 16/10/13.
//  Copyright © 2016年 赵鑫磊. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreAudioKit/CoreAudioKit.h>
@interface STAudioStreamBasicFormat : NSObject
+ (AudioStreamBasicDescription)inputFormat; // Alaya 的音频格式
+ (AudioStreamBasicDescription)wavFileFormat; // Wav 格式所需要的音频格式
+ (AudioStreamBasicDescription)aacFileFormat;  // aac 格式所需要的音频格式

@end
