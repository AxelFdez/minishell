#!/bin/bash

# Vérifie si Readline est installé
if ! brew list | grep -q readline; then

# Vérifie si Brew est installé
if ! command -v brew &> /dev/null; then

	# Installe Homebrew
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

    # Installe Readline
    brew install readline
fi
fi

# Affiche le chemin de la bibliothèque libreadline.a
echo "$(brew --prefix)/opt/readline/lib"