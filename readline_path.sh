#!/bin/bash

# Vérifie si Homebrew est installé
if ! command -v brew &> /dev/null; then
    # Installe Homebrew
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

# Vérifie si Readline est installé
if ! brew list | grep -q readline; then
    # Installe Readline
    brew install readline
fi

# Affiche le chemin de la bibliothèque libreadline.a
echo "$(brew --prefix)/opt/readline/lib"