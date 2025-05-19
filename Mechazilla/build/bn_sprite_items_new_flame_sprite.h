#ifndef BN_SPRITE_ITEMS_NEW_FLAME_SPRITE_H
#define BN_SPRITE_ITEMS_NEW_FLAME_SPRITE_H

#include "bn_sprite_item.h"

//{{BLOCK(new_flame_sprite_bn_gfx)

//======================================================================
//
//	new_flame_sprite_bn_gfx, 64x64@8, 
//	+ palette 48 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 96 + 4096 = 4192
//
//	Time-stamp: 2024-12-14, 23:48:56
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_NEW_FLAME_SPRITE_BN_GFX_H
#define GRIT_NEW_FLAME_SPRITE_BN_GFX_H

#define new_flame_sprite_bn_gfxTilesLen 4096
extern const bn::tile new_flame_sprite_bn_gfxTiles[128];

#define new_flame_sprite_bn_gfxPalLen 96
extern const bn::color new_flame_sprite_bn_gfxPal[48];

#endif // GRIT_NEW_FLAME_SPRITE_BN_GFX_H

//}}BLOCK(new_flame_sprite_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item new_flame_sprite(sprite_shape_size(sprite_shape::SQUARE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(new_flame_sprite_bn_gfxTiles, 128), bpp_mode::BPP_8, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(new_flame_sprite_bn_gfxPal, 48), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

