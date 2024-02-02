//
//  LuckTool.h
//  LuckBleSDK
//
//  Created by junky on 2023/9/18.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface LuckTool : NSObject

+ (NSData *)convertImageToBinaryData:(UIImage *)image;

+ (NSData *)blackWhiteProcessing:(UIImage *)bitmap;
+ (Byte)calculateEnc:(Byte *)data length:(NSUInteger)length;
+ (NSData *)dataFromInterger:(NSUInteger)inter length:(NSUInteger)length;

+ (UIImage *)scallImage:(UIImage *)image toWidth:(CGFloat)width;
+ (UIImage *)scallImage:(UIImage *)image toWidth:(CGFloat)width opaque:(BOOL)opaque;
+ (UIImage *)scallImage:(UIImage *)image toHeight:(CGFloat)height;

+ (UIImage *)scallImage:(UIImage *)image maxHeight:(CGFloat)maxH maxWidth:(CGFloat)maxW;

+ (UIImage *)scaleAndFillImage:(UIImage *)image toSize:(CGSize)targetSize;

+ (UIImage *)scaleAndClipWidthImage:(UIImage *)image toSize:(CGSize)targetSize;

+ (UIImage *)scaleAndClipHeightImage:(UIImage *)image toSize:(CGSize)targetSize;

+ (UIImage *)compressImage:(UIImage *)image maxLength:(NSInteger)maxLength;

+ (UIImage *)rotateImage:(UIImage *)image byDegrees:(CGFloat)degrees;

+ (UIImage *)dither:(UIImage *)image;

+ (UIImage *)gray:(UIImage *)image;

+ (UIImage *)erzhi:(UIImage *)image;

+ (UIImage *)adaptiveThresholdingForImage:(UIImage *)inputImage withWindowSize:(int)windowSize;

+ (UIImage *)drawWithWhiteBgImage:(UIImage *)image imgSize:(CGSize)imgSize bgSize:(CGSize)bgSize;

@end

NS_ASSUME_NONNULL_END
