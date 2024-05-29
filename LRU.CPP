#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <vector>
#include <map>
#include <random>

constexpr int NUM_PAGINAS = 10;
constexpr int MEM_FISICA_PAGINAS = 5;

std::map<int, int> tabela_paginas;
std::vector<int> memoria_fisica(MEM_FISICA_PAGINAS, -1);

class MemorySimulator : public QWidget {
    Q_OBJECT
public:
    MemorySimulator(QWidget *parent = nullptr) : QWidget(parent) {
        setupUi();
        connect(updateButton, &QPushButton::clicked, this, &MemorySimulator::acessarPagina);
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MemorySimulator::acessarPagina);
        timer->start(3000); // Acessa uma página aleatória a cada 3 segundos
    }

    void log(const QString &message) {
        logMessages->append(message);
    }

public slots:
    void acessarPagina() {
        int paginaVirtual = QTime::currentTime().msec() % NUM_PAGINAS;
        int paginaFisica = tabela_paginas[paginaVirtual];

        log(QString("Solicitando acesso à página %1.").arg(paginaVirtual));

        if (paginaFisica == -1) {
            log(QString("Page fault! Página %1 não está na memória.").arg(paginaVirtual));
            auto it = std::find(memoria_fisica.begin(), memoria_fisica.end(), -1);
            if (it != memoria_fisica.end()) {
                int paginaFisica = std::distance(memoria_fisica.begin(), it);
                log(QString("Alocando frame %1 para a página %2.").arg(paginaFisica).arg(paginaVirtual));
                memoria_fisica[paginaFisica] = paginaVirtual;
                tabela_paginas[paginaVirtual] = paginaFisica;
            } else {
                int paginaSubstituida = LRU();
                log(QString("Substituindo página %1 no frame %2 pela página %3.").arg(memoria_fisica[paginaSubstituida]).arg(paginaSubstituida).arg(paginaVirtual));
                tabela_paginas.erase(tabela_paginas.find(memoria_fisica[paginaSubstituida]));
                memoria_fisica[paginaSubstituida] = paginaVirtual;
                tabela_paginas[paginaVirtual] = paginaSubstituida;
            }
        } else {
            log(QString("Página %1 já está na memória no frame %2.").arg(paginaVirtual).arg(paginaFisica));
        }

        updateUI();
    }

private:
    void setupUi() {
        QVBoxLayout *layout = new QVBoxLayout(this);
        QLabel *infoLabel = new QLabel("Simulador de Paginação de Memória", this);
        layout->addWidget(infoLabel);
        updateButton = new QPushButton("Acessar Página Aleatória", this);
        layout->addWidget(updateButton);

        QGridLayout *gridLayout = new QGridLayout;
        layout->addLayout(gridLayout);

        for (int i = 0; i < NUM_PAGINAS; ++i) {
            QLabel *label = new QLabel(QString("Página %1: Não na memória").arg(i), this);
            label->setFrameStyle(QFrame::Box);
            label->setFixedSize(150, 40);
            pageLabels.push_back(label);
            gridLayout->addWidget(label, i / 5, i % 5);
        }

        for (int i = 0; i < MEM_FISICA_PAGINAS; ++i) {
            QLabel *label = new QLabel(QString("Frame %1: Vazio").arg(i), this);
            label->setFrameStyle(QFrame::Panel);
            label->setFixedSize(150, 40);
            memoryLabels.push_back(label);
            gridLayout->addWidget(label, 2 + i / 5, i % 5);
        }

        logMessages = new QTextEdit(this);
        logMessages->setReadOnly(true);
        layout->addWidget(logMessages);
    }

    int LRU() {
        int minIndex = 0;
        for (int i = 1; i < MEM_FISICA_PAGINAS; ++i) {
            if (tabela_paginas[memoria_fisica[i]] < tabela_paginas[memoria_fisica[minIndex]])
                minIndex = i;
        }
        return minIndex;
    }

    void updateUI() {
        for (int i = 0; i < NUM_PAGINAS; ++i) {
            pageLabels[i]->setText(QString("Página %1: %2").arg(i).arg(tabela_paginas[i] == -1 ? "Não na memória" : QString("Frame %1").arg(tabela_paginas[i])));
        }
        for (int i = 0; i < MEM_FISICA_PAGINAS; ++i) {
            memoryLabels[i]->setText(QString("Frame %1: %2").arg(i).arg(memoria_fisica[i] == -1 ? "Vazio" : QString("Página %1").arg(memoria_fisica[i])));
        }
    }

    QPushButton *updateButton;
    std::vector<QLabel*> pageLabels;
    std::vector<QLabel*> memoryLabels;
    QTextEdit *logMessages;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MemorySimulator simulator;
    simulator.setWindowTitle("Simulador de Paginação de Memória");
    simulator.show();
    return app.exec();
}

#include "main.moc"
