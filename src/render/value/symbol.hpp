//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <render/value/viewer.hpp>
#include <data/field/symbol.hpp>

// ----------------------------------------------------------------------------- : SymbolValueViewer

/// Viewer that displays a symbol value
class SymbolValueViewer : public ValueViewer {
public:
  DECLARE_VALUE_VIEWER(Symbol) : ValueViewer(parent,style) {}
  
  void draw(RotatedDC& dc) override;
  void onValueChange() override;
  
protected:
  vector<Bitmap> symbols;  ///< Cached images
};

