function rpm_static_build()
    darwin.dtw.copy_any_overwriting(
        "release/" .. PROJECT_NAME .. "static_linux.out",
        ".cache/rpm_static_build/SOURCES/" .. PROJECT_NAME .. "static_linux.out"
    )

    local formatted_rpm = [[
Name:           PROJECT_NAME
Version:        VERSION
Release:        1%{?dist}
Summary:        SUMARY
Source0:        PROJECT_NAME_static_linux.out

License:        LICENSE
URL:           PROJECT_URL

BuildRoot:      %{_tmppath}/%{name}-%{version}-buildroot
BuildArch:      x86_64

%description

DESCRIPITION

%prep

%build


%install
mkdir -p %{buildroot}/usr/local/bin
cp %{_sourcedir}/PROJECT_NAME_static_linux.out   %{buildroot}/usr/local/bin/PROJECT_NAME
chmod +x %{buildroot}/usr/local/bin/PROJECT_NAME
%files
/usr/local/bin/PROJECT_NAME

%changelog
* TIMEZONE - FULLNAME EMAIL  - 1.0.0-1
- YOUR_CHANGES
]]

    formatted_rpm = string.gsub(formatted_rpm, "PROJECT_NAME", PROJECT_NAME)
    formatted_rpm = string.gsub(formatted_rpm, "VERSION", VERSION)
    formatted_rpm = string.gsub(formatted_rpm, "SUMARY", SUMARY)
    formatted_rpm = string.gsub(formatted_rpm, "LICENSE", LICENSE)
    formatted_rpm = string.gsub(formatted_rpm, "DESCRIPITION", DESCRIPITION)
    formatted_rpm = string.gsub(formatted_rpm, "PROJECT_URL", URL)
    formatted_rpm = string.gsub(formatted_rpm, "FULLNAME", FULLNAME)
    formatted_rpm = string.gsub(formatted_rpm, "TIMEZONE", os.date("%a %b %d %Y"))
    formatted_rpm = string.gsub(formatted_rpm, "EMAIL", EMAIL)

    darwin.dtw.write_file(".cache/rpm_static_build/SPECS/project.spec", formatted_rpm)
    os.execute("mkdir -p .cache/rpm_static_build/RPMS")

    local image = darwin.ship.create_machine("almalinux:latest")
    image.provider = CONTANIZER
    image.add_comptime_command("dnf install rpm-build rpmdevtools -y")
    image.add_comptime_command("dnf install gcc -y")
    image.add_comptime_command("rpmdev-setuptree")

    image.start({
        flags = {"-it"},
        volumes = {
            {"./.cache/rpm_static_build/SOURCES", "/root/rpmbuild/SOURCES"},
            {"./.cache/rpm_static_build/SPECS", "/root/rpmbuild/SPECS"},
            {"./.cache/rpm_static_build/RPMS", "/root/rpmbuild/RPMS"}
        },
        command = "rpmbuild -ba ~/rpmbuild/SPECS/project.spec"
    })

    local rpms = darwin.dtw.list_files_recursively(".cache/rpm_static_build/RPMS", true)
    for _, file in ipairs(rpms) do
        if darwin.dtw.ends_with(file, ".rpm") then
            -- it will have only one rpm
            darwin.dtw.copy_any_overwriting(file, "release/" .. PROJECT_NAME .. ".rpm")
            break
        end
    end

    print("\tRPM package build completed")
end

darwin.add_recipe({
    name = "rpm",
    requires = {"static_linux"},
    description = "Create an RPM package from the static linux binary",
    outs = {"release/" .. PROJECT_NAME .. ".rpm"},
    inputs = {"src", "dependencies", "builds"},
    callback = rpm_static_build
})