#ifndef BN_AFFINE_BG_ITEMS_EXAMPLE_H
#define BN_AFFINE_BG_ITEMS_EXAMPLE_H

#include "bn_affine_bg_item.h"

//{{BLOCK(example_bn_gfx)

//======================================================================
//
//	example_bn_gfx, 128x128@8, 
//	+ palette 32 entries, not compressed
//	+ 95 tiles (t reduced) not compressed
//	+ affine map, not compressed, 16x16 
//	Total size: 64 + 6080 + 256 = 6400
//
//	Time-stamp: 2024-12-14, 23:48:56
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_EXAMPLE_BN_GFX_H
#define GRIT_EXAMPLE_BN_GFX_H

#define example_bn_gfxTilesLen 6080
extern const bn::tile example_bn_gfxTiles[190];

#define example_bn_gfxMapLen 256
extern const bn::affine_bg_map_cell example_bn_gfxMap[256];

#define example_bn_gfxPalLen 64
extern const bn::color example_bn_gfxPal[32];

#endif // GRIT_EXAMPLE_BN_GFX_H

//}}BLOCK(example_bn_gfx)

namespace bn::affine_bg_items
{
    constexpr inline affine_bg_item example(
            affine_bg_tiles_item(span<const tile>(example_bn_gfxTiles, 190), compression_type::NONE), 
            bg_palette_item(span<const color>(example_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE),
            affine_bg_map_item(example_bn_gfxMap[0], size(16, 16), compression_type::NONE, 1, false));
}

#endif

