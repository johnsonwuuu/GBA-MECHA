#ifndef BN_REGULAR_BG_ITEMS_STAGE1_H
#define BN_REGULAR_BG_ITEMS_STAGE1_H

#include "bn_regular_bg_item.h"

//{{BLOCK(stage1_bn_gfx)

//======================================================================
//
//	stage1_bn_gfx, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 369 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 23616 + 2048 = 26176
//
//	Time-stamp: 2024-12-14, 23:48:56
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE1_BN_GFX_H
#define GRIT_STAGE1_BN_GFX_H

#define stage1_bn_gfxTilesLen 23616
extern const bn::tile stage1_bn_gfxTiles[738];

#define stage1_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell stage1_bn_gfxMap[1024];

#define stage1_bn_gfxPalLen 512
extern const bn::color stage1_bn_gfxPal[256];

#endif // GRIT_STAGE1_BN_GFX_H

//}}BLOCK(stage1_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item stage1(
            regular_bg_tiles_item(span<const tile>(stage1_bn_gfxTiles, 738), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(stage1_bn_gfxPal, 256), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(stage1_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

