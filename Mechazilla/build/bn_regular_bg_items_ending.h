#ifndef BN_REGULAR_BG_ITEMS_ENDING_H
#define BN_REGULAR_BG_ITEMS_ENDING_H

#include "bn_regular_bg_item.h"

//{{BLOCK(ending_bn_gfx)

//======================================================================
//
//	ending_bn_gfx, 256x256@8, 
//	+ palette 144 entries, not compressed
//	+ 702 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 288 + 44928 + 2048 = 47264
//
//	Time-stamp: 2024-12-14, 23:48:56
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ENDING_BN_GFX_H
#define GRIT_ENDING_BN_GFX_H

#define ending_bn_gfxTilesLen 44928
extern const bn::tile ending_bn_gfxTiles[1404];

#define ending_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell ending_bn_gfxMap[1024];

#define ending_bn_gfxPalLen 288
extern const bn::color ending_bn_gfxPal[144];

#endif // GRIT_ENDING_BN_GFX_H

//}}BLOCK(ending_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item ending(
            regular_bg_tiles_item(span<const tile>(ending_bn_gfxTiles, 1404), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(ending_bn_gfxPal, 144), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(ending_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

