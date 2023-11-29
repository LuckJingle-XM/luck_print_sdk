//
//  LuckPrinterInfo.h
//  LuckBleSDK
//
//  Created by junky on 2023/10/31.
//

//#import <LuckBleSDK/LuckBleSDK.h>
#import <Foundation/Foundation.h>
#import <LuckBleSDK/LuckLabelSize.h>


NS_ASSUME_NONNULL_BEGIN



typedef NS_ENUM(NSUInteger, LPManufacturerType) {
    LPManufacturerAY,
    LPManufacturerJRP,
};

/// 纸张类型
typedef NS_ENUM(NSUInteger, LPPaperType) {
    // 卷纸
    LPPaperTypeJZ = 0x10,
    // 折叠纸
    LPPaperTypeZD = 0x30,
};


/// 状态
typedef NS_OPTIONS(NSUInteger, LPPrinterState) {
    // 打印中
    LPPrinterStatePrinting = 1 << 0,
    // 开盖
    LPPrinterStateOpenCover = 1 << 1,
    // 缺纸
    LPPrinterStateOutPaper = 1 << 2,
    // 低电
    LPPrinterStatePower = 1 << 3,
    // 过热
    LPPrinterStateHot = 1 << 4,
    // 繁忙
    LPPrinterStateBusy = 1 << 6
};


@interface LuckPrinterInfo : NSObject


/// uuid
@property (nonatomic , copy) NSUUID *uuid;

/// 厂家
@property (nonatomic , readonly) LPManufacturerType manufacturer;

/// 型号
@property (nonatomic , copy) NSString *model;

/// 蓝牙名字
@property (nonatomic , copy) NSString *name;

/// mac地址
@property (nonatomic , copy) NSString *mac;

/// sn
@property (nonatomic , copy) NSString *sn;

/// 固件版本
@property (nonatomic , copy) NSString *version;

/// 状态
@property (nonatomic , assign) LPPrinterState state;

/// 浓度，设置浓度后，打印前会给设备设置浓度，默认适中 1
@property (nonatomic , assign) NSUInteger thick;

/// 关机时间
@property (nonatomic , assign) NSUInteger closeTime;

/// 电量
@property (nonatomic , assign) NSUInteger power;

/// 打印速度
@property (nonatomic , assign) NSUInteger speed;

/// 点密度
@property (nonatomic , readonly) NSUInteger dpi;

/// 支持的宽度 如：2 in 54mm
@property (nonatomic , readonly) NSArray <NSString *>*supportWidthFormm;

/// 当前纸张类型 A4才支持
@property (nonatomic , assign) LPPaperType paperType;

/// 支持的标签尺寸
@property (nonatomic , readonly) NSArray <LuckLabelSize *>*supportLabelSizes;

/// 当前标签尺寸
@property (nonatomic , strong) LuckLabelSize *labelSize;


/// 是否是A4
@property (nonatomic , readonly) BOOL isA4Model;

/// 是否是mini
@property (nonatomic , readonly) BOOL isMiniModel;

/// 是否是面单
@property (nonatomic , readonly) BOOL isMDModel;


/// 面单机的属性
@property (nonatomic , assign) int gapM;

/// 面单机的size
@property (nonatomic , assign) CGFloat mdWidth;

/// 面单机的size
@property (nonatomic , assign) CGFloat mdHeight;

/// 面单机的M
@property (nonatomic , assign) NSUInteger mdM;


/// 走纸长度，设备需要走纸时用到
@property (nonatomic , readonly) NSUInteger walkLong;

/// 最大支持浓度
@property (nonatomic , readonly) NSUInteger maxDensity;

/// 最大支持的速度
@property (nonatomic , readonly) NSUInteger maxSpeed;


/// 最后连接的设备， 目前没用
+ (LuckPrinterInfo *)lastConnectPrinter;

/// 设置为最后连接的设备， 目前没用
- (void)setToLastConnectPrinter;






@end

NS_ASSUME_NONNULL_END
