//
//  STCircularBufferModel.h
//  ExternalAccessorySample
//
//  Created by 赵鑫磊 on 16/3/22.
//  Copyright © 2016年 赵鑫磊. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface STCircularBufferModel : NSObject

@property (nonatomic, assign, readonly) void *circularBufferRef;
@property (nonatomic, assign, readonly) SInt32 availableReadBytes;
- (BOOL)creatCircularBufferWithSize:(SInt32)byteSize;
- (instancetype)initWithCircularBufferSize:(SInt32)byteSize;
- (void)reset;
- (void)appendWithDataByte:(Byte *)dataByte byteLength:(UInt32)byteLength;
- (Byte *)readByteFromCircularWithLength:(SInt32)byteLength;
- (Byte *)tailOfAvailableReadBytes:(SInt32 *)availableBytes;
@end
