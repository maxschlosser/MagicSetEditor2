//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/locale.hpp>
#include <util/reflect.hpp>
#include <util/io/package.hpp>

DECLARE_POINTER_TYPE(Locale);
DECLARE_POINTER_TYPE(SubLocale);
DECLARE_POINTER_TYPE(SubLocaleValidator);

// ----------------------------------------------------------------------------- : Locale class

/// Translations of the texts of a locale category or game/stylesheet/symbolfont
class SubLocale : public IntrusivePtrBase<SubLocale> {
public:
  unordered_map<String,String> translations;
  
  /// Translate a key, if not found, apply the default function to the key
  String tr(const String& key, DefaultLocaleFun def) const;
  String tr(const String& subcat, const String& key, DefaultLocaleFun def) const;
  
  DECLARE_REFLECTION();
};

/// A collection of translations of messages
class Locale : public Packaged {
public:
  /// Translations of UI strings in each category
  SubLocale              translations[LOCALE_CAT_MAX];
  /// Translations of Package specific texts, by relativeFilename
  map<String,SubLocaleP> package_translations;
  
  /// Open a locale with the given name
  static LocaleP byName(const String& name);
  
protected:
  String typeName() const override;
  Version fileVersion() const override;
  DECLARE_REFLECTION();
};

/// The global locale object
extern LocaleP the_locale;

