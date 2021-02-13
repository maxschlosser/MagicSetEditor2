//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/reflect.hpp>
#include <script/scriptable.hpp>

DECLARE_POINTER_TYPE(WordListWord);
DECLARE_POINTER_TYPE(WordList);
DECLARE_POINTER_TYPE(AutoReplace);

// ----------------------------------------------------------------------------- : WordList

/// A word in a WordList
class WordListWord : public IntrusivePtrBase<WordListWord> {
public:
  WordListWord();

  String  name;         ///< Name of the list / the word
  bool    line_below;   ///< Line below in the list?
  bool    is_prefix;    ///< Is this a prefix before other words?
  vector<WordListWordP> words; ///< Sublist
  OptionalScript script;  ///< Generate words using a script

  inline bool isGroup() const { return !words.empty(); }

  DECLARE_REFLECTION();
};

/// A list of words for a drop down box
class WordList : public WordListWord {
public:
  DECLARE_REFLECTION();
};

// ----------------------------------------------------------------------------- : Auto replace words

/// Autoreplace specific shortcut words
class AutoReplace : public IntrusivePtrVirtualBase {
public:
  AutoReplace();

  bool   enabled;
  bool   whole_word;
  bool   custom; ///< Is this a custom auto replace?
  String match;
  String replace;

  inline AutoReplaceP clone() const { return make_intrusive<AutoReplace>(*this); }

  DECLARE_REFLECTION();
};

void after_reading(AutoReplace& ar, Version);

