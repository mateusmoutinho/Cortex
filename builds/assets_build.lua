local function write_bytes(assets_stream, file_stream)
    local size = 0
    local is_binary = false
    while true do
        local chunk = file_stream:read(1024)
        if not chunk then break end
        size = size + #chunk
        for i = 1, #chunk do
            local byte = string.byte(chunk, i)
            if byte == 0 then
                is_binary = true
            end
            assets_stream:write(string.format("%d,", byte))
        end
    end
    return {
        size = size,
        is_binary = is_binary
    }
end

local function embed_assets()

    -- Write assets.h (struct definition and extern declaration)
    local header = io.open("assets.h", "w")
    if not header then
        error("Failed to open assets.h for writing")
    end
    header:write([[
#ifndef ASSETS_H
#define ASSETS_H

typedef struct app_embedded_asset {
    const char *path;
    unsigned char *content;
    unsigned long  size;
    int is_binary;
} app_embedded_asset;

extern app_embedded_asset embedded_assets[];
extern unsigned long embedded_assets_total_size;

#endif
]])
    header:close()

    -- Write assets.c (data)
    local assets_stream = io.open("assets.c", "w")
    if not assets_stream then
        error("Failed to open assets.c for writing")
    end
    assets_stream:write('#include "assets.h"\n\n')
    assets_stream:write("app_embedded_asset embedded_assets[] = {\n")


    local assets_files = darwin.dtw.list_files_recursively(ASSETS_DIR)
    local total_size = #assets_files
    for i=1, #assets_files do

        assets_stream:write("{\n.path = \"" .. assets_files[i] .. "\",\n .content = (unsigned char[]){")

        local file_stream = io.open("assets/"..assets_files[i], "rb")
        if not file_stream then
            error("Failed to open file: " .. assets_files[i])
        end
    local props  = write_bytes(assets_stream, file_stream)
        file_stream:close()
        assets_stream:write("},\n .size = " .. props.size .. ",\n .is_binary = " .. (props.is_binary and 1 or 0) .. "\n},\n")
   

    end

    assets_stream:write("};\n")
    assets_stream:write("\nunsigned long embedded_assets_total_size = " .. total_size .. ";\n")
    assets_stream:close()
end

darwin.add_recipe({
    name = "assets",
    description = "Embed assets into assets.h and assets.c",
    outs = {"assets.h", "assets.c"},
    inputs = {"assets", "builds"},
    callback = function()
        print("\tStarting assets embedding")
        embed_assets()
        print("\tAssets embedding completed")
    end
})
