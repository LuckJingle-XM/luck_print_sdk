#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ImageDataProcesser : NSObject

+ (ImageDataProcesser *)ImageDataInstance;
/**
 * 标准方法
 * @param img 图片
 */
-(NSData *) bmpToDataNormal:(UIImage *)bitmap;

/**
 * 标准方法
 *
 * @param bmpData 处理后数据
 * @param width 图片宽度
 * @param height 图片高度
 */
-(NSData *) bmpDateToDataNormal:(NSData *)bmpData Width:(int32_t)width Height:(int32_t) height;

/**
 * LuckP机器用的压缩方法
 * @param img 图片
 */
-(NSData *) bmpToDataWithLuckP:(UIImage *)img;
/**
 * LuckP机器用的压缩方法
 *
 * @param bmpData 处理后数据
 * @param width 图片宽度
 * @param height 图片高度

 */
-(NSData *) bmpDataToDataWithLuckP:(NSData *)bmpData Width:(int32_t)width Height:(int32_t) height;
/**
 * A80机器用的压缩方法
 * @param img 图片
 */

-(NSData *) bmpToDataWithA8:(UIImage *)bitmap;
/**
 * A80机器用的压缩方法
 *
 * @param bmpData 处理后数据
 * @param width 图片宽度
 * @param height 图片高度
 * @param mode   0：正常打印；1：倍宽打印；2：倍高打印； 3：倍宽倍高打印
 */
-(NSData *) bmpDataToDataWithA80:(NSData *)bmpData Width:(int32_t)width Height:(int32_t) height;
/**
 *
 * @param x 横坐标
 * @param start_y 纵坐标
 * @param img 图片
 */
-(NSData *)DrawPicTSPL:(NSInteger)x start_y:(NSInteger)y img:(UIImage*)img;


@end
