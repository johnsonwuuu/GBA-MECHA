#ifndef BN_SPRITE_ITEMS_FLAME_SPRITE_H
#define BN_SPRITE_ITEMS_FLAME_SPRITE_H

#include "bn_sprite_item.h"

//{{BLOCK(flame_sprite_bn_gfx)

//======================================================================
//
//	flame_sprite_bn_gfx, 64x64@8, 
//	+ palette 32 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 64 + 4096 = 4160
//
//	Time-stamp: 2024-12-03, 07:08:49
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FLAME_SPRITE_BN_GFX_H
#define GRIT_FLAME_SPRITE_BN_GFX_H

#define flame_sprite_bn_gfxTilesLen 4096
extern const bn::tile flame_sprite_bn_gfxTiles[128];

#define flame_sprite_bn_gfxPalLen 64
extern const bn::color flame_sprite_bn_gfxPal[32];

#endif // GRIT_FLAME_SPRITE_BN_GFX_H

//}}BLOCK(flame_sprite_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item flame_sprite(sprite_shape_size(sprite_shape::SQUARE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(flame_sprite_bn_gfxTiles, 128), bpp_mode::BPP_8, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(flame_sprite_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

