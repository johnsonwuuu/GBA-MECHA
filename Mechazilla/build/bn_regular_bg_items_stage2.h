#ifndef BN_REGULAR_BG_ITEMS_STAGE2_H
#define BN_REGULAR_BG_ITEMS_STAGE2_H

#include "bn_regular_bg_item.h"

//{{BLOCK(stage2_bn_gfx)

//======================================================================
//
//	stage2_bn_gfx, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 453 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 28992 + 2048 = 31552
//
//	Time-stamp: 2024-12-14, 23:48:56
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE2_BN_GFX_H
#define GRIT_STAGE2_BN_GFX_H

#define stage2_bn_gfxTilesLen 28992
extern const bn::tile stage2_bn_gfxTiles[906];

#define stage2_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell stage2_bn_gfxMap[1024];

#define stage2_bn_gfxPalLen 512
extern const bn::color stage2_bn_gfxPal[256];

#endif // GRIT_STAGE2_BN_GFX_H

//}}BLOCK(stage2_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item stage2(
            regular_bg_tiles_item(span<const tile>(stage2_bn_gfxTiles, 906), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(stage2_bn_gfxPal, 256), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(stage2_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

