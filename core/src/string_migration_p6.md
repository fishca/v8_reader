# P6 - LegacyText cleanup in core

## Current state
- Direct VCL includes are absent from core/src and core/include.
- Legacy RTL text usage is now isolated behind the `LegacyText` alias.
- Public/domain metadata DTOs are moved toward `Utf16String`.
- Full project build passes via `Compile/build.bat`.

## Next migration target
1. Replace `LegacyText` in `Parse_tree.*` with `Utf16String` and std helpers.
2. Replace `LegacyText` in `ModuleTextStorage.cpp` and `ModuleTextEncodingUtils.h` with `Utf16String`/byte-vector codecs.
3. Move remaining RTL conversion adapters to `src` only.
4. Keep building after every file group.

## Completion criteria
- `rg -n "\\bLegacyText\\b" core/src core/include` returns 0.
- No RTL/VCL text aliases remain in core public headers.
- `Compile/build.bat` stays green.
