// SPDX-License-Identifier: GPL-2.0-or-later

// included header files
#include "samsungmn_int.hpp"
#include "i18n.h"  // NLS support.
#include "image_int.hpp"
#include "tags.hpp"
#include "tags_int.hpp"
#include "types.hpp"
#include "value.hpp"

// + standard includes
#include <ostream>

// *****************************************************************************
// class member definitions
namespace Exiv2::Internal {
//! LensType, tag 0xa003
constexpr TagDetails samsung2LensType[] = {
    {0, N_("Built-in")},
    {1, "Samsung NX 30mm F2 Pancake"},
    {2, "Samsung NX 18-55mm F3.5-5.6 OIS"},
    {3, "Samsung NX 50-200mm F4-5.6 ED OIS"},
    {4, "Samsung NX 20-50mm F3.5-5.6 ED"},
    {5, "Samsung NX 20mm F2.8 Pancake"},
    {6, "Samsung NX 18-200mm F3.5-6.3 ED OIS"},
    {7, "Samsung NX 60mm F2.8 Macro ED OIS SSA"},
    {8, "Samsung NX 16mm F2.4 Pancake"},
    {9, "Samsung NX 85mm F1.4 ED SSA"},
    {10, "Samsung NX 45mm F1.8"},
    {11, "Samsung NX 45mm F1.8 2D/3D"},
    {12, "Samsung NX 12-24mm F4-5.6 ED"},
    {13, "Samsung NX 16-50mm F2-2.8 S ED OIS"},
    {14, "Samsung NX 10mm F3.5 Fisheye"},
    {15, "Samsung NX 16-50mm F3.5-5.6 Power Zoom ED OIS"},
    {20, "Samsung NX 50-150mm F2.8 S ED OIS"},
    {21, "Samsung NX 300mm F2.8 ED OIS"},
};

//! ColorSpace, tag 0xa011
constexpr TagDetails samsung2ColorSpace[] = {
    {0, N_("sRGB")},
    {1, N_("Adobe RGB")},
};

//! SmartRange, tag 0xa012
constexpr TagDetails samsung2SmartRange[] = {
    {0, N_("Off")},
    {1, N_("On")},
};

//! Print the camera temperature
static std::ostream& printCameraTemperature(std::ostream& os, const Value& value, const ExifData*) {
  if (value.count() != 1 || value.typeId() != signedRational) {
    return os << value;
  }
  return os << value.toFloat() << " C";
}

//! Print the 35mm focal length
static std::ostream& printFocalLength35(std::ostream& os, const Value& value, const ExifData*) {
  if (value.count() != 1 || value.typeId() != unsignedLong) {
    return os << value;
  }
  auto length = value.toInt64();
  if (length == 0) {
    return os << _("Unknown");
  }
  return os << stringFormat("{:.1f} mm", length / 10.0);
}

// Samsung MakerNote Tag Info
constexpr TagInfo Samsung2MakerNote::tagInfo_[] = {
    {0x0001, "Version", N_("Version"), N_("Makernote version"), IfdId::samsung2Id, SectionId::makerTags, undefined, -1,
     printExifVersion},
    {0x0021, "PictureWizard", N_("Picture Wizard"), N_("Picture wizard composite tag"), IfdId::samsung2Id,
     SectionId::makerTags, unsignedShort, -1, printValue},
    {0x0030, "LocalLocationName", N_("Local Location Name"), N_("Local location name"), IfdId::samsung2Id,
     SectionId::makerTags, asciiString, -1, printValue},
    {0x0031, "LocationName", N_("Location Name"), N_("Location name"), IfdId::samsung2Id, SectionId::makerTags,
     asciiString, -1, printValue},
    {0x0035, "Preview", N_("Pointer to a preview image"), N_("Offset to an IFD containing a preview image"),
     IfdId::samsung2Id, SectionId::makerTags, unsignedLong, -1, printValue},
    {0x0043, "CameraTemperature", N_("Camera Temperature"), N_("Camera temperature"), IfdId::samsung2Id,
     SectionId::makerTags, signedRational, -1, printCameraTemperature},
    {0xa001, "FirmwareName", N_("Firmware Name"), N_("Firmware name"), IfdId::samsung2Id, SectionId::makerTags,
     asciiString, -1, printValue},
    {0xa003, "LensType", N_("Lens Type"), N_("Lens type"), IfdId::samsung2Id, SectionId::makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(samsung2LensType)},
    {0xa004, "LensFirmware", N_("Lens Firmware"), N_("Lens firmware"), IfdId::samsung2Id, SectionId::makerTags,
     asciiString, -1, printValue},
    {0xa010, "SensorAreas", N_("Sensor Areas"), N_("Sensor areas"), IfdId::samsung2Id, SectionId::makerTags,
     unsignedLong, -1, printValue},
    {0xa011, "ColorSpace", N_("Color Space"), N_("Color space"), IfdId::samsung2Id, SectionId::makerTags, unsignedShort,
     -1, EXV_PRINT_TAG(samsung2ColorSpace)},
    {0xa012, "SmartRange", N_("Smart Range"), N_("Smart range"), IfdId::samsung2Id, SectionId::makerTags, unsignedShort,
     -1, EXV_PRINT_TAG(samsung2SmartRange)},
    {0xa013, "ExposureBiasValue", N_("Exposure Bias Value"), N_("Exposure bias value"), IfdId::samsung2Id,
     SectionId::makerTags, signedRational, -1, print0x9204},
    {0xa014, "ISO", N_("ISO"), N_("ISO"), IfdId::samsung2Id, SectionId::makerTags, unsignedLong, -1, printValue},
    {0xa018, "ExposureTime", N_("Exposure Time"), N_("Exposure time"), IfdId::samsung2Id, SectionId::makerTags,
     unsignedRational, -1, print0x829a},
    {0xa019, "FNumber", N_("FNumber"), N_("The F number."), IfdId::samsung2Id, SectionId::makerTags, unsignedRational,
     -1, print0x829d},
    {0xa01a, "FocalLengthIn35mmFormat", N_("Focal Length In 35mm Format"), N_("Focal length in 35mm format"),
     IfdId::samsung2Id, SectionId::makerTags, unsignedLong, -1, printFocalLength35},
    {0xa020, "EncryptionKey", N_("Encryption Key"), N_("Encryption key"), IfdId::samsung2Id, SectionId::makerTags,
     unsignedLong, -1, printValue},
    {0xa021, "WB_RGGBLevelsUncorrected", N_("WB RGGB Levels Uncorrected"),
     N_("WB RGGB levels not corrected for WB_RGGBLevelsBlack"), IfdId::samsung2Id, SectionId::makerTags, unsignedLong,
     -1, printValue},
    {0xa022, "WB_RGGBLevelsAuto", N_("WB RGGB Levels Auto"), N_("WB RGGB levels auto"), IfdId::samsung2Id,
     SectionId::makerTags, unsignedLong, -1, printValue},
    {0xa023, "WB_RGGBLevelsIlluminator1", N_("WB RGGB Levels Illuminator1"), N_("WB RGGB levels illuminator1"),
     IfdId::samsung2Id, SectionId::makerTags, unsignedLong, -1, printValue},
    {0xa024, "WB_RGGBLevelsIlluminator2", N_("WB RGGB Levels Illuminator2"), N_("WB RGGB levels illuminator2"),
     IfdId::samsung2Id, SectionId::makerTags, unsignedLong, -1, printValue},
    {0xa028, "WB_RGGBLevelsBlack", N_("WB RGGB Levels Black"), N_("WB RGGB levels black"), IfdId::samsung2Id,
     SectionId::makerTags, signedLong, -1, printValue},
    {0xa030, "ColorMatrix", N_("Color Matrix"), N_("Color matrix"), IfdId::samsung2Id, SectionId::makerTags, signedLong,
     -1, printValue},
    {0xa031, "ColorMatrixSRGB", N_("Color Matrix sRGB"), N_("Color matrix sRGB"), IfdId::samsung2Id,
     SectionId::makerTags, signedLong, -1, printValue},
    {0xa032, "ColorMatrixAdobeRGB", N_("Color Matrix Adobe RGB"), N_("Color matrix Adobe RGB"), IfdId::samsung2Id,
     SectionId::makerTags, signedLong, -1, printValue},
    {0xa040, "ToneCurve1", N_("Tone Curve 1"), N_("Tone curve 1"), IfdId::samsung2Id, SectionId::makerTags,
     unsignedLong, -1, printValue},
    {0xa041, "ToneCurve2", N_("Tone Curve 2"), N_("Tone curve 2"), IfdId::samsung2Id, SectionId::makerTags,
     unsignedLong, -1, printValue},
    {0xa042, "ToneCurve3", N_("Tone Curve 3"), N_("Tone curve 3"), IfdId::samsung2Id, SectionId::makerTags,
     unsignedLong, -1, printValue},
    {0xa043, "ToneCurve4", N_("Tone Curve 4"), N_("Tone curve 4"), IfdId::samsung2Id, SectionId::makerTags,
     unsignedLong, -1, printValue},
    // End of list marker
    {0xffff, "(UnknownSamsung2MakerNoteTag)", "(UnknownSamsung2MakerNoteTag)", N_("Unknown Samsung2MakerNote tag"),
     IfdId::samsung2Id, SectionId::makerTags, undefined, -1, printValue},
};

const TagInfo* Samsung2MakerNote::tagList() {
  return tagInfo_;
}

//! PictureWizard Mode
constexpr TagDetails samsungPwMode[] = {
    {0, N_("Standard")}, {1, N_("Vivid")},   {2, N_("Portrait")}, {3, N_("Landscape")},
    {4, N_("Forest")},   {5, N_("Retro")},   {6, N_("Cool")},     {7, N_("Calm")},
    {8, N_("Classic")},  {9, N_("Custom1")}, {10, N_("Custom2")}, {11, N_("Custom3")},
};

//! Print the PictureWizard Color tag value
static std::ostream& printPwColor(std::ostream& os, const Value& value, const ExifData*) {
  if (value.count() != 1 || value.typeId() != unsignedShort) {
    return os << value;
  }
  // Special case where no color modification is done
  if (value.toInt64() == 65535) {
    return os << _("Neutral");
  }
  // Output seems to represent Hue in degrees
  return os << value.toInt64();
}

//! Print the tag value minus 4
static std::ostream& printValueMinus4(std::ostream& os, const Value& value, const ExifData*) {
  if (value.count() != 1 || value.typeId() != unsignedShort) {
    return os << value;
  }
  return os << value.toInt64(0) - 4;
}

// Samsung PictureWizard Tag Info
constexpr TagInfo Samsung2MakerNote::tagInfoPw_[] = {
    {0x0000, "Mode", N_("Mode"), N_("Mode"), IfdId::samsungPwId, SectionId::makerTags, unsignedShort, 1,
     EXV_PRINT_TAG(samsungPwMode)},
    {0x0001, "Color", N_("Color"), N_("Color"), IfdId::samsungPwId, SectionId::makerTags, unsignedShort, 1,
     printPwColor},
    {0x0002, "Saturation", N_("Saturation"), N_("Saturation"), IfdId::samsungPwId, SectionId::makerTags, unsignedShort,
     1, printValueMinus4},
    {0x0003, "Sharpness", N_("Sharpness"), N_("Sharpness"), IfdId::samsungPwId, SectionId::makerTags, unsignedShort, 1,
     printValueMinus4},
    {0x0004, "Contrast", N_("Contrast"), N_("Contrast"), IfdId::samsungPwId, SectionId::makerTags, unsignedShort, 1,
     printValueMinus4},
    // End of list marker
    {0xffff, "(UnknownSamsungPictureWizardTag)", "(UnknownSamsungPictureWizardTag)",
     N_("Unknown SamsungPictureWizard tag"), IfdId::samsungPwId, SectionId::makerTags, unsignedShort, 1, printValue},
};

const TagInfo* Samsung2MakerNote::tagListPw() {
  return tagInfoPw_;
}

}  // namespace Exiv2::Internal
