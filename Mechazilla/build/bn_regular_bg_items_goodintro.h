#ifndef BN_REGULAR_BG_ITEMS_GOODINTRO_H
#define BN_REGULAR_BG_ITEMS_GOODINTRO_H

#include "bn_regular_bg_item.h"

//{{BLOCK(goodintro_bn_gfx)

//======================================================================
//
//	goodintro_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 431 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 13792 + 2048 = 15872
//
//	Time-stamp: 2024-12-14, 23:48:56
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GOODINTRO_BN_GFX_H
#define GRIT_GOODINTRO_BN_GFX_H

#define goodintro_bn_gfxTilesLen 13792
extern const bn::tile goodintro_bn_gfxTiles[431];

#define goodintro_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell goodintro_bn_gfxMap[1024];

#define goodintro_bn_gfxPalLen 32
extern const bn::color goodintro_bn_gfxPal[16];

#endif // GRIT_GOODINTRO_BN_GFX_H

//}}BLOCK(goodintro_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item goodintro(
            regular_bg_tiles_item(span<const tile>(goodintro_bn_gfxTiles, 431), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(goodintro_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(goodintro_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

