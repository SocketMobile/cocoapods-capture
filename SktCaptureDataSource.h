/**
  @file SktCaptureDataSource.h
  @brief Define the Data Source object in Capture

  @copyright © 2017 Socket Mobile, Inc.

 */

#ifndef SktCaptureDataSource_h
#define SktCaptureDataSource_h

/**

 @brief idenfity a barcode symbology or a RFID/NFC Tag

 */
typedef NS_ENUM(NSInteger, SKTCaptureDataSourceID) {
    /** Data Source ID is not specified */
    SKTCaptureDataSourceIDNotSpecified,
    /** Australia Post symbology */
    SKTCaptureDataSourceIDSymbologyAustraliaPost,
    /** Aztec symbology */
    SKTCaptureDataSourceIDSymbologyAztec,
    /** Bookland EAN symbology */
    SKTCaptureDataSourceIDSymbologyBooklandEan,
    /** British Post symbology */
    SKTCaptureDataSourceIDSymbologyBritishPost,
    /** Canada Post symbology */
    SKTCaptureDataSourceIDSymbologyCanadaPost,
    /** Chinese 2 of 5 symbology */
    SKTCaptureDataSourceIDSymbologyChinese2of5,
    /** Codabar symbology */
    SKTCaptureDataSourceIDSymbologyCodabar,
    /** Codablock A symbology */
    SKTCaptureDataSourceIDSymbologyCodablockA,
    /** Codablock F symbology */
    SKTCaptureDataSourceIDSymbologyCodablockF,
    /** Code 11 symbology */
    SKTCaptureDataSourceIDSymbologyCode11,
    /** Code 39 symbology */
    SKTCaptureDataSourceIDSymbologyCode39,
    /** Code 39 extended symbology */
    SKTCaptureDataSourceIDSymbologyCode39Extended,
    /** Code 39 trioptic symbology */
    SKTCaptureDataSourceIDSymbologyCode39Trioptic,
    /** Code 93 symbology */
    SKTCaptureDataSourceIDSymbologyCode93,
    /** Code 128 symbology */
    SKTCaptureDataSourceIDSymbologyCode128,
    /** Data Matrix symbology */
    SKTCaptureDataSourceIDSymbologyDataMatrix,
    /** Dutch Post symbology */
    SKTCaptureDataSourceIDSymbologyDutchPost,
    /** EAN 8 symbology */
    SKTCaptureDataSourceIDSymbologyEan8,
    /** EAN 13 symbology */
    SKTCaptureDataSourceIDSymbologyEan13,
    /** EAN 128 symbology */
    SKTCaptureDataSourceIDSymbologyEan128,
    /** EAN 128 Irregular symbology */
    SKTCaptureDataSourceIDSymbologyEan128Irregular,
    /** EAN UCC Composite AB symbology */
    SKTCaptureDataSourceIDSymbologyEanUccCompositeAB,
    /** EAN UCC Composite C symbology */
    SKTCaptureDataSourceIDSymbologyEanUccCompositeC,
    /** GS1 Databar symbology */
    SKTCaptureDataSourceIDSymbologyGs1Databar,
    /** GS1 Databar symbology */
    SKTCaptureDataSourceIDSymbologyGs1DatabarLimited,
    /** GS1 Databar Expanded symbology */
    SKTCaptureDataSourceIDSymbologyGs1DatabarExpanded,
    /** Interleaved 2 of 5 symbology */
    SKTCaptureDataSourceIDSymbologyInterleaved2of5,
    /** ISBT 128 symbology */
    SKTCaptureDataSourceIDSymbologyIsbt128,
    /** Japan Post symbology */
    SKTCaptureDataSourceIDSymbologyJapanPost,
    /** Matrix 2 of 5 symbology */
    SKTCaptureDataSourceIDSymbologyMatrix2of5,
    /** Maxicode symbology */
    SKTCaptureDataSourceIDSymbologyMaxicode,
    /** MSI symbology */
    SKTCaptureDataSourceIDSymbologyMsi,
    /** PDF 417 symobology */
    SKTCaptureDataSourceIDSymbologyPdf417,
    /** PDF 417 Micro symbology */
    SKTCaptureDataSourceIDSymbologyPdf417Micro,
    /** Planet symbology */
    SKTCaptureDataSourceIDSymbologyPlanet,
    /** Plessey symbology */
    SKTCaptureDataSourceIDSymbologyPlessey,
    /** Postnet symbology */
    SKTCaptureDataSourceIDSymbologyPostnet,
    /** QR Code symbology */
    SKTCaptureDataSourceIDSymbologyQRCode,
    /** also called Industrial 2 of 5 or Discrete 2 of 5 */
    SKTCaptureDataSourceIDSymbologyStandard2of5,
    /** Telepen symbology */
    SKTCaptureDataSourceIDSymbologyTelepen,
    /** TLC39 symbology */
    SKTCaptureDataSourceIDSymbologyTlc39,
    /** UPC-A symbology */
    SKTCaptureDataSourceIDSymbologyUpcA,
    /** UPC-E0 symbology */
    SKTCaptureDataSourceIDSymbologyUpcE0,
    /** UPC-E3 symbology */
    SKTCaptureDataSourceIDSymbologyUpcE1,
    /** USPS Intelligent Mail symbology */
    SKTCaptureDataSourceIDSymbologyUspsIntelligentMail,
    /** Direct Part Marking symbology */
    SKTCaptureDataSourceIDSymbologyDirectPartMarking,
    /** HanXin symbology */
    SKTCaptureDataSourceIDSymbologyHanXin,
    /** marks the end of symbology IDs, not an actual Symbology ID */
    SKTCaptureDataSourceIDSymbologyLastSymbologyID,
};

/**

 @brief define the data source status

 */
typedef NS_ENUM(NSInteger, SKTCaptureDataSourceStatus) {
    /** data source is or should be disabled */
    SKTCaptureDataSourceStatusDisabled,
    /** data source is or should be enabled */
    SKTCaptureDataSourceStatusEnabled,
    /** data source is not supported */
    SKTCaptureDataSourceStatusNotSupported
};

/**

 @brief define the flag value of a data source structure

 */
typedef NS_OPTIONS(NSInteger, SKTCaptureDataSourceFlags) {
    /** the data source structure contains only a status */
    SKTCaptureDataSourceFlagsStatus=1,
};

/**
 @class SKTCaptureDataSource

 @brief define a data source which has an ID, a name and a status. The flag is set to
 status because for now that is the only parameter the data source can have
 */
@interface SKTCaptureDataSource : NSObject

/**
 Get or Set the Data Source ID
 */
@property SKTCaptureDataSourceID ID;

/**
 contain the data source name
 */
@property (nullable, nonatomic, strong) NSString* Name;

/**
 contain the data source status (enabled or disable or not supported)
 */
@property SKTCaptureDataSourceStatus Status;

/**
 contain the flag that defines the data source argument, today always set to status
 */
@property SKTCaptureDataSourceFlags Flags;
@end
#endif /* SktCaptureDataSource_h */
