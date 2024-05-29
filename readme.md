## README - Simulador de Paginação de Memória com LRU Em C++

**Introdução:**

Este repositório contém um simulador de paginação de memória em C++ que utiliza o algoritmo LRU (Least Recently Used) para substituição de página. O simulador possui uma interface gráfica simples que permite visualizar o estado da memória física e as estatísticas de acesso à memória.

Trabalho proposto pelo professor rafael Borges com intuito na obtenção de nota da N2
elaborado pelo aluno Denilson Oliveira da Silva do curso de ciencia da computação PUC goias

**Funcionalidades:**

* Simula a alocação de páginas virtuais na memória física.
* Implementa o algoritmo LRU para substituição de página.
* Exibe o estado da memória física e as estatísticas de acesso à memória em uma interface gráfica.
* Permite o acesso aleatório a páginas virtuais a cada 3 segundos.
* Permite o acesso manual a páginas virtuais clicando nos labels da interface.

**Requisitos:**

* Compilador C++
* Qt Framework ([https://www.qt.io/](https://www.qt.io/))

**Instalação:**

1. Clone o repositório:

```bash
git clone https://github.com/seu-usuario/simulador-paginacao-memoria.git
```

2. Instale as dependências do Qt:

```bash
sudo apt-get install qt5-default qtcreator qt5-qmake qt5-dev libqt5-core libqt5-gui libqt5-widgets libqt5-opengl5 libqt5-quickcontrols2 libqt5-designer libqt5-svg libqt5-dbus libqt5-gstreamer1.0 libqt5-multimedia libqt5-network libqt5-printsupport libqt5-sql libqt5-webkit libqt5-webengine libqt5-x11extras libqt5-xcb libqt5-openssl libqt5-icu libqt5-xml libqt5-imageformats libqt5-libpng libqt5-libjpeg libqt5-libtiff libqt5-libwebp libqt5-dbus libqt5-gstreamer1.0 libqt5-multimedia libqt5-network libqt5-printsupport libqt5-sql libqt5-webkit libqt5-webengine libqt5-x11extras libqt5-xcb libqt5-openssl libqt5-icu libqt5-xml libqt5-imageformats libqt5-libpng libqt5-libjpeg libqt5-libtiff libqt5-libwebp
```

3. Abra o projeto `main.pro` no Qt Creator e compile o código.
4. Execute o executável gerado.

**Uso:**

* A interface gráfica será exibida com informações sobre o estado da memória física e as estatísticas de acesso à memória.
* Clique no botão "Acessar Página Aleatória" para gerar um acesso aleatório a uma página virtual.
* Clique nos labels das páginas virtuais para gerar um acesso manual à página.
* Observe como o estado da memória física e as estatísticas de acesso à memória são atualizadas após cada acesso à página.

**Configurações:**

* O número de páginas virtuais e o número de frames na memória física podem ser modificados nas constantes `NUM_PAGINAS` e `MEM_FISICA_PAGINAS` no arquivo `main.cpp`.
* O intervalo de tempo entre os acessos aleatórios à página pode ser modificado no construtor da classe `MemorySimulator` no arquivo `main.cpp`.

**Observações:**

* O código assume que todas as páginas virtuais têm o mesmo tamanho.
* O código não implementa a busca na memória secundária para carregar páginas que não estão na memória física.
* O código pode ser aprimorado para incluir métricas de desempenho, como taxa de page faults e tempo médio de acesso à memória.

**Contribuições:**

Sinta-se à vontade para contribuir com este projeto reportando bugs, sugerindo melhorias ou enviando patches.

**Agradecimentos:**

Agradeço a todos que contribuíram para este projeto.
