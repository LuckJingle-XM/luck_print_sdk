//
//  LuckLabelSize.h
//  LuckBleSDK
//
//  Created by junky on 2023/10/17.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LuckLabelSize : NSObject

/// 标签的显示文本 50mm * 20mm
@property (nonatomic , readonly) NSString *labelTitle;

/// 宽度显示文本 2 in 50mm
@property (nonatomic , readonly) NSString *widthTitle;


/// 变迁宽度
@property (nonatomic , readonly)CGFloat labelW;

/// 标签高度
@property (nonatomic , readonly)CGFloat labelH;

/// 对应纸张宽度
@property (nonatomic , readonly) CGFloat paperlW;

/// 对饮纸张高度
@property (nonatomic , readonly) CGFloat paperH;


/// 实际打印的宽度
@property (nonatomic , readonly) CGFloat drawW;

/// 实际打印的高度
@property (nonatomic , readonly) CGFloat drawH;



- (instancetype)initWithLabelW:(CGFloat)w labelH:(CGFloat)h;


/// 宽度为12的尺寸合集
+ (NSArray <LuckLabelSize *>*)labelList12;

+ (NSArray <LuckLabelSize *>*)labelList14;

/// 宽度为40的尺寸合集
+ (NSArray <LuckLabelSize *>*)labelList40;

/// 宽度为50的尺寸合集
+ (NSArray <LuckLabelSize *>*)labelList50;

/// 宽度为74的尺寸合集
+ (NSArray <LuckLabelSize *>*)labelList74;

/// 宽度为100的尺寸合集
+ (NSArray <LuckLabelSize *>*)labelList100;

/// 面单
+ (NSArray <LuckLabelSize *>*)labelList80;

/// A4
+ (instancetype)a4;

/// Letter
+ (instancetype)letter;





@end

NS_ASSUME_NONNULL_END
