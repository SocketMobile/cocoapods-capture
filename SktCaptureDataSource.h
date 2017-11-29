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
    SKTCaptureDataSourceIDNotSpecified, /** Data Source ID is not specified */
    SKTCaptureDataSourceIDSymbologyAustraliaPost, /** Australia Post symbology */
    SKTCaptureDataSourceIDSymbologyAztec, /** Aztec symbology */
    SKTCaptureDataSourceIDSymbologyBooklandEan, /** Bookland EAN symbology */
    SKTCaptureDataSourceIDSymbologyBritishPost, /** British Post symbology */
    SKTCaptureDataSourceIDSymbologyCanadaPost, /** Canada Post symbology */
    SKTCaptureDataSourceIDSymbologyChinese2of5, /** Chinese 2 of 5 symbology */
    SKTCaptureDataSourceIDSymbologyCodabar, /** Codabar symbology */
    SKTCaptureDataSourceIDSymbologyCodablockA, /** Codablock A symbology */
    SKTCaptureDataSourceIDSymbologyCodablockF, /** Codablock F symbology */
    SKTCaptureDataSourceIDSymbologyCode11, /** Code 11 symbology */
    SKTCaptureDataSourceIDSymbologyCode39, /** Code 39 symbology */
    SKTCaptureDataSourceIDSymbologyCode39Extended, /** Code 39 extended symbology */
    SKTCaptureDataSourceIDSymbologyCode39Trioptic, /** Code 39 trioptic symbology */
    SKTCaptureDataSourceIDSymbologyCode93, /** Code 93 symbology */
    SKTCaptureDataSourceIDSymbologyCode128, /** Code 128 symbology */
    SKTCaptureDataSourceIDSymbologyDataMatrix, /** Data Matrix symbology */
    SKTCaptureDataSourceIDSymbologyDutchPost, /** Dutch Post symbology */
    SKTCaptureDataSourceIDSymbologyEan8, /** EAN 8 symbology */
    SKTCaptureDataSourceIDSymbologyEan13, /** EAN 13 symbology */
    SKTCaptureDataSourceIDSymbologyEan128, /** EAN 128 symbology */
    SKTCaptureDataSourceIDSymbologyEan128Irregular, /** EAN 128 Irregular symbology */
    SKTCaptureDataSourceIDSymbologyEanUccCompositeAB, /** EAN UCC Composite AB symbology */
    SKTCaptureDataSourceIDSymbologyEanUccCompositeC, /** EAN UCC Composite C symbology */
    SKTCaptureDataSourceIDSymbologyGs1Databar, /** GS1 Databar symbology */
    SKTCaptureDataSourceIDSymbologyGs1DatabarLimited, /** GS1 Databar symbology */
    SKTCaptureDataSourceIDSymbologyGs1DatabarExpanded, /** GS1 Databar Expanded symbology */
    SKTCaptureDataSourceIDSymbologyInterleaved2of5, /** Interleaved 2 of 5 symbology */
    SKTCaptureDataSourceIDSymbologyIsbt128, /** ISBT 128 symbology */
    SKTCaptureDataSourceIDSymbologyJapanPost, /** Japan Post symbology */
    SKTCaptureDataSourceIDSymbologyMatrix2of5, /** Matrix 2 of 5 symbology */
    SKTCaptureDataSourceIDSymbologyMaxicode, /** Maxicode symbology */
    SKTCaptureDataSourceIDSymbologyMsi, /** MSI symbology */
    SKTCaptureDataSourceIDSymbologyPdf417, /** PDF 417 symobology */
    SKTCaptureDataSourceIDSymbologyPdf417Micro, /** PDF 417 Micro symbology */
    SKTCaptureDataSourceIDSymbologyPlanet, /** Planet symbology */
    SKTCaptureDataSourceIDSymbologyPlessey, /** Plessey symbology */
    SKTCaptureDataSourceIDSymbologyPostnet, /** Postnet symbology */
    SKTCaptureDataSourceIDSymbologyQRCode, /** QR Code symbology */
    SKTCaptureDataSourceIDSymbologyStandard2of5, /** also called Industrial 2 of 5 or Discrete 2 of 5 */
    SKTCaptureDataSourceIDSymbologyTelepen, /** Telepen symbology */
    SKTCaptureDataSourceIDSymbologyTlc39, /** TLC39 symbology */
    SKTCaptureDataSourceIDSymbologyUpcA, /** UPC-A symbology */
    SKTCaptureDataSourceIDSymbologyUpcE0, /** UPC-E0 symbology */
    SKTCaptureDataSourceIDSymbologyUpcE1, /** UPC-E3 symbology */
    SKTCaptureDataSourceIDSymbologyUspsIntelligentMail, /** USPS Intelligent Mail symbology */
    SKTCaptureDataSourceIDSymbologyDirectPartMarking, /** Direct Part Marking symbology */
    SKTCaptureDataSourceIDSymbologyHanXin, /** HanXin symbology */
    SKTCaptureDataSourceIDSymbologyLastSymbologyID, /** marks the end of symbology IDs, not an actual Symbology ID */
};

/**

 @brief define the data source status

 */
typedef NS_ENUM(NSInteger, SKTCaptureDataSourceStatus) {
    SKTCaptureDataSourceStatusDisabled, /** data source is or should be disabled */
    SKTCaptureDataSourceStatusEnabled, /** data source is or should be enabled */
    SKTCaptureDataSourceStatusNotSupported /** data source is not supported */
};

/**

 @brief define the flag value of a data source structure

 */
typedef NS_OPTIONS(NSInteger, SKTCaptureDataSourceFlags) {
    SKTCaptureDataSourceFlagsStatus=1, /** the data source structure contains only a status */
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
