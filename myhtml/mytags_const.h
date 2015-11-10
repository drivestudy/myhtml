//
//  mytags_const.h
//  myhtml
//
//  Created by Alexander Borisov on 29.09.15.
//  Copyright (c) 2015 Alexander Borisov. All rights reserved.
//

#ifndef myhtml_mytags_const_h
#define myhtml_mytags_const_h

enum mytags_tag {
	MyTAGS_TAG__TEXT = 1,
// comment tag <!-->,
	MyTAGS_TAG__COMMENT = 2,
	MyTAGS_TAG__DOCTYPE = 3,
	MyTAGS_TAG_A = 4,
	MyTAGS_TAG_ABBR = 5,
	MyTAGS_TAG_ACRONYM = 6,
	MyTAGS_TAG_ADDRESS = 7,
	MyTAGS_TAG_APPLET = 8,
	MyTAGS_TAG_AREA = 9,
	MyTAGS_TAG_ARTICLE = 10,
	MyTAGS_TAG_ASIDE = 11,
	MyTAGS_TAG_AUDIO = 12,
	MyTAGS_TAG_B = 13,
	MyTAGS_TAG_BASE = 14,
	MyTAGS_TAG_BASEFONT = 15,
	MyTAGS_TAG_BDI = 16,
	MyTAGS_TAG_BDO = 17,
	MyTAGS_TAG_BGSOUND = 18,
	MyTAGS_TAG_BIG = 19,
	MyTAGS_TAG_BLINK = 20,
	MyTAGS_TAG_BLOCKQUOTE = 21,
	MyTAGS_TAG_BODY = 22,
	MyTAGS_TAG_BR = 23,
	MyTAGS_TAG_BUTTON = 24,
	MyTAGS_TAG_CANVAS = 25,
	MyTAGS_TAG_CAPTION = 26,
	MyTAGS_TAG_CENTER = 27,
	MyTAGS_TAG_CITE = 28,
	MyTAGS_TAG_CODE = 29,
	MyTAGS_TAG_COL = 30,
	MyTAGS_TAG_COLGROUP = 31,
	MyTAGS_TAG_COMMAND = 32,
	MyTAGS_TAG_COMMENT = 33,
	MyTAGS_TAG_DATALIST = 34,
	MyTAGS_TAG_DD = 35,
	MyTAGS_TAG_DEL = 36,
	MyTAGS_TAG_DETAILS = 37,
	MyTAGS_TAG_DFN = 38,
	MyTAGS_TAG_DIR = 39,
	MyTAGS_TAG_DIV = 40,
	MyTAGS_TAG_DL = 41,
	MyTAGS_TAG_DT = 42,
	MyTAGS_TAG_EM = 43,
	MyTAGS_TAG_EMBED = 44,
	MyTAGS_TAG_FIELDSET = 45,
	MyTAGS_TAG_FIGCAPTION = 46,
	MyTAGS_TAG_FIGURE = 47,
	MyTAGS_TAG_FONT = 48,
	MyTAGS_TAG_FOOTER = 49,
	MyTAGS_TAG_FORM = 50,
	MyTAGS_TAG_FRAME = 51,
	MyTAGS_TAG_FRAMESET = 52,
	MyTAGS_TAG_H1 = 53,
	MyTAGS_TAG_H2 = 54,
	MyTAGS_TAG_H3 = 55,
	MyTAGS_TAG_H4 = 56,
	MyTAGS_TAG_H5 = 57,
	MyTAGS_TAG_H6 = 58,
	MyTAGS_TAG_HEAD = 59,
	MyTAGS_TAG_HEADER = 60,
	MyTAGS_TAG_HGROUP = 61,
	MyTAGS_TAG_HR = 62,
	MyTAGS_TAG_HTML = 63,
	MyTAGS_TAG_I = 64,
	MyTAGS_TAG_IFRAME = 65,
	MyTAGS_TAG_IMG = 66,
	MyTAGS_TAG_INPUT = 67,
	MyTAGS_TAG_INS = 68,
	MyTAGS_TAG_ISINDEX = 69,
	MyTAGS_TAG_KBD = 70,
	MyTAGS_TAG_KEYGEN = 71,
	MyTAGS_TAG_LABEL = 72,
	MyTAGS_TAG_LEGEND = 73,
	MyTAGS_TAG_LI = 74,
	MyTAGS_TAG_LINK = 75,
	MyTAGS_TAG_MAP = 76,
	MyTAGS_TAG_MARK = 77,
	MyTAGS_TAG_MARQUEE = 78,
	MyTAGS_TAG_MENU = 79,
	MyTAGS_TAG_META = 80,
	MyTAGS_TAG_METER = 81,
	MyTAGS_TAG_NAV = 82,
	MyTAGS_TAG_NOBR = 83,
	MyTAGS_TAG_NOEMBED = 84,
	MyTAGS_TAG_NOFRAMES = 85,
	MyTAGS_TAG_NOSCRIPT = 86,
	MyTAGS_TAG_OBJECT = 87,
	MyTAGS_TAG_OL = 88,
	MyTAGS_TAG_OPTGROUP = 89,
	MyTAGS_TAG_OPTION = 90,
	MyTAGS_TAG_OUTPUT = 91,
	MyTAGS_TAG_P = 92,
	MyTAGS_TAG_PARAM = 93,
	MyTAGS_TAG_PLAINTEXT = 94,
	MyTAGS_TAG_PRE = 95,
	MyTAGS_TAG_PROGRESS = 96,
	MyTAGS_TAG_Q = 97,
	MyTAGS_TAG_RP = 98,
	MyTAGS_TAG_RT = 99,
	MyTAGS_TAG_RUBY = 100,
	MyTAGS_TAG_S = 101,
	MyTAGS_TAG_SAMP = 102,
	MyTAGS_TAG_SCRIPT = 103,
	MyTAGS_TAG_SECTION = 104,
	MyTAGS_TAG_SELECT = 105,
	MyTAGS_TAG_SMALL = 106,
	MyTAGS_TAG_SOURCE = 107,
	MyTAGS_TAG_SPAN = 108,
	MyTAGS_TAG_STRIKE = 109,
	MyTAGS_TAG_STRONG = 110,
	MyTAGS_TAG_STYLE = 111,
	MyTAGS_TAG_SUB = 112,
	MyTAGS_TAG_SUMMARY = 113,
	MyTAGS_TAG_SUP = 114,
	MyTAGS_TAG_TABLE = 115,
	MyTAGS_TAG_TBODY = 116,
	MyTAGS_TAG_TD = 117,
	MyTAGS_TAG_TEXTAREA = 118,
	MyTAGS_TAG_TFOOT = 119,
	MyTAGS_TAG_TH = 120,
	MyTAGS_TAG_THEAD = 121,
	MyTAGS_TAG_TIME = 122,
	MyTAGS_TAG_TITLE = 123,
	MyTAGS_TAG_TR = 124,
	MyTAGS_TAG_TRACK = 125,
	MyTAGS_TAG_TT = 126,
	MyTAGS_TAG_U = 127,
	MyTAGS_TAG_UL = 128,
	MyTAGS_TAG_VAR = 129,
	MyTAGS_TAG_VIDEO = 130,
	MyTAGS_TAG_WBR = 131,
	MyTAGS_TAG_XMP = 132,
	MyTAGS_TAG_FIRST_ENTRY = 1,
	MyTAGS_TAG_LAST_ENTRY = 133
};

#endif
