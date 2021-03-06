//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <render/value/viewer.hpp>
#include <data/field/image.hpp>

DECLARE_POINTER_TYPE(AlphaMask);

// ----------------------------------------------------------------------------- : ImageValueViewer

/// Viewer that displays an image value
class ImageValueViewer : public ValueViewer {
public:
  DECLARE_VALUE_VIEWER(Image) : ValueViewer(parent,style) {}
  
  void draw(RotatedDC& dc) override;
  void onValueChange() override;
  void onStyleChange(int) override;
      
private:
  Bitmap bitmap; ///< Cached bitmap
  RealSize size; ///< Size of cached bitmap
  Radians angle;  ///< Angle of cached bitmap
  bool    is_default; ///< Is the default placeholder image used?
  
  /// Generate a placeholder image
  static Bitmap imagePlaceholder(const Rotation& rot, UInt w, UInt h, const Image& background, bool editing);
};

