
function local_linux_bin_build()
    
    local build_props = {
        cflags = CFLAGS or ""
    }

    local compiler = "gcc"
    if LAUNGUAGE == "cpp" then
        compiler = "g++"
    end
   
    local compilation = compiler.." "..build_props.cflags.." -o Quill src/main.c  libs/doTheWorld.o libs/CWebStudio.o libs/cJSON.o libs/UniversalGarbage.o libs/UniversalSocket.o libs/CTextEngine.o libs/CArgvParse.o  libs/LuaCEmbed.o -ldl"

    print("compilation: ", compilation)
    os.execute(compilation)

    print("\tLocal Linux binary build completed")
end

darwin.add_recipe({
    inputs={
        "dependencies",
        "src",
        "builds",
        "libs"
    },
    outs= {
        "Quill"
    },
    name="local_unix_bin",
    requires={"local_objects_libs","silver_chain_organize"},
    description = "Build static object files and link them into a local Linux binary",
    callback = local_linux_bin_build
})