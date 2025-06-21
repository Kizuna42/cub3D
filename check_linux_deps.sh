#!/bin/bash

echo "🔍 Checking Linux dependencies for cub3D..."

# Check if we're on Linux
if [[ "$OSTYPE" != "linux-gnu"* ]]; then
    echo "❌ This script is for Linux only"
    exit 1
fi

# Function to check if package is installed
check_package() {
    local package=$1
    local description=$2
    
    if dpkg -l | grep -q "^ii  $package "; then
        echo "✅ $description ($package) - installed"
        return 0
    elif rpm -qa | grep -q "$package" 2>/dev/null; then
        echo "✅ $description ($package) - installed"
        return 0
    else
        echo "❌ $description ($package) - NOT installed"
        return 1
    fi
}

# Check required packages
missing_packages=()

echo ""
echo "📦 Checking required packages:"

if ! check_package "libx11-dev\|libX11-devel" "X11 development libraries"; then
    missing_packages+=("libx11-dev")
fi

if ! check_package "libxext-dev\|libXext-devel" "X11 extension libraries"; then
    missing_packages+=("libxext-dev")
fi

if ! check_package "zlib1g-dev\|zlib-devel" "Zlib development libraries"; then
    missing_packages+=("zlib1g-dev")
fi

# Check if gcc/make are available
echo ""
echo "🔧 Checking build tools:"

if command -v gcc &> /dev/null; then
    echo "✅ GCC compiler - available"
else
    echo "❌ GCC compiler - NOT available"
    missing_packages+=("gcc")
fi

if command -v make &> /dev/null; then
    echo "✅ Make build tool - available"
else
    echo "❌ Make build tool - NOT available"
    missing_packages+=("make")
fi

# Provide installation instructions if packages are missing
if [ ${#missing_packages[@]} -gt 0 ]; then
    echo ""
    echo "⚠️  Missing packages detected!"
    echo ""
    echo "📋 To install missing packages:"
    echo ""
    echo "For Ubuntu/Debian:"
    echo "sudo apt update"
    echo "sudo apt install ${missing_packages[*]}"
    echo ""
    echo "For CentOS/RHEL/Fedora:"
    echo "sudo yum install libX11-devel libXext-devel zlib-devel gcc make"
    echo "# or for newer versions:"
    echo "sudo dnf install libX11-devel libXext-devel zlib-devel gcc make"
    echo ""
    exit 1
else
    echo ""
    echo "🎉 All dependencies are satisfied!"
    echo "You can now run 'make' to build cub3D"
    echo ""
fi 