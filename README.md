# Cortex
Cortex its a sandbox template for creating web applications in C. It provides a set of functions and types to handle HTTP requests, responses, JSON parsing, and memory management. The main goal of Cortex is to allow developers to create web applications by vibecoding in C, without worrying about the underlying implementation details.

# Create a Web Application with Cortex

## Step 1: Fork these repository
for these repo by clicking in "use as template" and then "fork". This will create a copy of the repository in your GitHub account.

## Step 2: Clone your forked repository
Clone the repository to your local machine using the following command:
```bash
git clone https://github.com/your-username/your-forked-repo.git
```
## Step 3: Pass the [app.c](app.c) file to a llm
copy the content of the [app.c](app.c) file and pass it to a llm (like chatgpt) with a prompt like these:
```markdown
using these sandbox, create a url shortener web application :
endpoints:
- GET /: returns a simple HTML page with a form to submit a URL to be shortened.
- POST /shorten: receives a JSON object with a "url" field and returns a JSON object with a "short_url" field containing the shortened URL.
- GET /redirect/{shortid}: receives a short URL and redirects to the original URL.
storage schema:
store the original urls into a dir called "urls", with these format:
----
urls/
  <shorten_id>.txt
  <shorten_id2>.txt
----
```

## Step 4: Build and run the application
now you can chose from the followin building ways:

### Simple gcc compilation
these template its compilation ready, you can compile the application using gcc with the following command:

requirements:
- gcc must be installed in your system.

```bash
gcc main.c -o app
```
then you can run the application with:
```bash
./app
```
### Amalgamation
you can create a single `.c`containing all the code of the application, including the cortex code with darwin. 
requirements:
- Darwin must be installed in your system.

~~~bash
 darwin run_blueprint --target amalgamation
~~~
this will create a file [release/Cortex.c](release/Cortex.c) with all the code of the application, then you can compile it with:
```bash
gcc release/Cortex.c -o app
```
and run it with:
```bash
./app
```
### Static Linux Binary
you can create a static binary for your application using Darwin with the following command:
```bash
darwin run_blueprint --target static_linux --provider docker
```
### Windows Executable
you can create a windows executable for your application using Darwin with the following command:
```bash
darwin run_blueprint --target windows --provider docker
```

### .Deb or .rpm package
you can create a .deb or .rpm package for your application using Darwin with the following command:
```bash
darwin run_blueprint --target deb --provider docker
```
or
```bash
darwin run_blueprint --target rpm --provider docker
```
### Debug Run 
you can run the application in debug mode, which will automatically rebuild the debug.so dynamic library whenever the source code changes and run the application with it. to do that, you can use the following command:
```bash
darwin run_blueprint --target debug --compiler "gcc"
```


### Build Requirements
these parts, describe how to install the required dependencies to build the application.

## gcc or clang
to install gcc or clang, you can follow the instructions in their official websites:
- [GCC Installation Guide](https://gcc.gnu.org/install/)
- [Clang Installation Guide](https://clang.llvm.org/get_started.html)
if you are using a debian-based linux distribution, you can use the following command:
```bash
sudo apt-get install build-essential
```
if you are using macOS, you can install gcc or clang by installing the Xcode Command Line Tools with the following command:
```bash
xcode-select --install
```


### [Darwin](https://github.com/OUIsolutions/Darwin) 
to install [Darwin](https://github.com/OUIsolutions/Darwin), you can navegate to the [releases page](https://github.com/OUIsolutions/Darwin/releases/tag/0.20.0) and download the precompiled binary for your operating system.
if you are using linux, you can use the following command:
(note that curl must be installed)
```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.20.0/darwin_linux_bin.out -o darwin.out && chmod +x darwin.out &&   mv darwin.out /usr/local/bin/darwin 
```
if you are using macOS, you can use the following command:
(note that curl and gcc must be installed)
```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.20.0/darwin.c -o darwin.c && gcc darwin.c -o darwin.out && sudo mv darwin.out /usr/local/bin/darwin && rm darwin.c 
```

### [Docker](https://www.docker.com/) or [Podman](https://podman.io/)
to install [Docker](https://www.docker.com/) or [Podman](https://podman.io/), you can follow the instructions in their official websites:
- [Docker Installation Guide](https://docs.docker.com/get-docker/)
- [Podman Installation Guide](https://podman.io/getting-started/installation)
note that you can chose from docker or podman, by passing --provider at any [Darwin](https://github.com/OUIsolutions/Darwin)  command you want.

### [CWebStudioFirmware](https://github.com/OUIsolutions/CWebStudioFirmware)
to install [CWebStudioFirmware](https://github.com/OUIsolutions/CWebStudioFirmware) you can navegate to the [releases page](https://github.com/OUIsolutions/CWebStudioFirmware/releases/tag/0.7.0) and download the precompiled binary for your operating system.

if you are using linux or macos, you can use the following command:
(note that curl must be installed)
```bash
curl -L https://github.com/OUIsolutions/CWebStudioFirmware/releases/download/0.7.0/CWebStudioFirmware.c -o CWebStudioFirmware.c && gcc CWebStudioFirmware.c -o CWebStudioFirmware.out && sudo mv CWebStudioFirmware.out /usr/local/bin/CWebStudioFirmware && rm CWebStudioFirmware.c 
```



