function create_objects_ar_libs()
    local compiler = "gcc"
    if LAUNGUAGE == "cpp" then
        compiler = "g++"
    end
    os.execute("mkdir -p libs")
    local itens = {

        {command=compiler.." -c dependencies/CArgvParse.c -o libs/CArgvParse.o",out_path="libs/CArgvParse.o"},
        {command=compiler.." -c dependencies/CTextEngine.c -o libs/CTextEngine.o",out_path="libs/CTextEngine.o"},
        {command=compiler.." -c dependencies/UniversalGarbage.c -o libs/UniversalGarbage.o",out_path="libs/UniversalGarbage.o"},
        {command=compiler.." -c dependencies/cJSON.c -o libs/cJSON.o",out_path="libs/cJSON.o"},
        {command=compiler.." -c dependencies/UniversalSocket.c  -o libs/UniversalSocket.o",out_path="libs/UniversalSocket.o"},
        {command=compiler.." -c dependencies/LuaCEmbed.c  -DLUA_CEMBED_MOCK_UNIVERSAL_GARBAGE_DEFINE -o libs/LuaCEmbed.o",out_path="libs/LuaCEmbed.o"},
        {command=compiler.." -c dependencies/CWebStudio.c  -DCWEB_MOCK_CJSON_DEFINE -DCWEB_MOCK_UNIVERSAL_GARBAGE_DEFINE -DCWEB_MOCK_UNIVERSAL_SOCKET_DEFINE  -DCWEB_MOCK_CTEXT_ENGINE_DEFINE -o libs/CWebStudio.o",out_path="libs/CWebStudio.o"},
        {command=compiler..[[ -c dependencies/doTheWorldOne.c -DDTW_MOCK_CJSON_DEFINE    -o libs/doTheWorld.o]],out_path="libs/doTheWorld.o"},

    }

    for _, item in ipairs(itens) do
            os.execute(item.command)
    end

end 

function local_linux_libs_build()
    create_objects_ar_libs()
    
    print("\tLocal Linux libraries (.o objects) build completed")
end

darwin.add_recipe({
    inputs={
        "dependencies",
        "builds"
    },
    outs= {
        "libs/CArgvParse.o",
        "libs/CTextEngine.o", 
        "libs/UniversalGarbage.o",
        "libs/cJSON.o",
        "libs/UniversalSocket.o",
        "libs/LuaCEmbed.o",
        "libs/CWebStudio.o",
        "libs/doTheWorld.o"
    },
    name="local_objects_libs",
    requires={},
    description = "Build static object files (.o) for local Linux development",
    callback = local_linux_libs_build
})