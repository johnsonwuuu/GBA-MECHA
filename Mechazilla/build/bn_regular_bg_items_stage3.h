#ifndef BN_REGULAR_BG_ITEMS_STAGE3_H
#define BN_REGULAR_BG_ITEMS_STAGE3_H

#include "bn_regular_bg_item.h"

//{{BLOCK(stage3_bn_gfx)

//======================================================================
//
//	stage3_bn_gfx, 256x256@8, 
//	+ palette 224 entries, not compressed
//	+ 644 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 448 + 41216 + 2048 = 43712
//
//	Time-stamp: 2024-12-14, 23:48:56
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE3_BN_GFX_H
#define GRIT_STAGE3_BN_GFX_H

#define stage3_bn_gfxTilesLen 41216
extern const bn::tile stage3_bn_gfxTiles[1288];

#define stage3_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell stage3_bn_gfxMap[1024];

#define stage3_bn_gfxPalLen 448
extern const bn::color stage3_bn_gfxPal[224];

#endif // GRIT_STAGE3_BN_GFX_H

//}}BLOCK(stage3_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item stage3(
            regular_bg_tiles_item(span<const tile>(stage3_bn_gfxTiles, 1288), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(stage3_bn_gfxPal, 224), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(stage3_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

