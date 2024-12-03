#ifndef BN_SPRITE_ITEMS_MECHAZILLA_H
#define BN_SPRITE_ITEMS_MECHAZILLA_H

#include "bn_sprite_item.h"

//{{BLOCK(mechazilla_bn_gfx)

//======================================================================
//
//	mechazilla_bn_gfx, 64x64@8, 
//	+ palette 240 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 480 + 4096 = 4576
//
//	Time-stamp: 2024-12-03, 07:08:49
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MECHAZILLA_BN_GFX_H
#define GRIT_MECHAZILLA_BN_GFX_H

#define mechazilla_bn_gfxTilesLen 4096
extern const bn::tile mechazilla_bn_gfxTiles[128];

#define mechazilla_bn_gfxPalLen 480
extern const bn::color mechazilla_bn_gfxPal[240];

#endif // GRIT_MECHAZILLA_BN_GFX_H

//}}BLOCK(mechazilla_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item mechazilla(sprite_shape_size(sprite_shape::SQUARE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(mechazilla_bn_gfxTiles, 128), bpp_mode::BPP_8, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(mechazilla_bn_gfxPal, 240), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

