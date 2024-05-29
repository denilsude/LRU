import tkinter as tk
import random

# Configurações iniciais
NUM_PAGINAS = 10  # Número de páginas virtuais
MEM_FISICA_PAGINAS = 5  # Número de frames na memória física

# Dicionário para representar a tabela de páginas
# Chave: número da página virtual, Valor: número da página física ou None se não estiver na memória
tabela_paginas = {i: None for i in range(NUM_PAGINAS)}

# Lista para simular os frames de memória física
memoria_fisica = [None] * MEM_FISICA_PAGINAS

class Application(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack(expand=True, fill='both')
        self.create_widgets()

    def create_widgets(self):
        self.lbl_info = tk.Label(self, text="Simulador de Paginação de Memória", font=("Arial", 16))
        self.lbl_info.pack(pady=10)

        self.update_display = tk.Button(self, text="Acessar Página Aleatória", command=self.acessar_pagina)
        self.update_display.pack(pady=10)

        self.tables_frame = tk.Frame(self)
        self.tables_frame.pack()

        # Tabela de páginas
        self.page_labels = {}
        for i in range(NUM_PAGINAS):
            lbl = tk.Label(self.tables_frame, text=f'Página {i}: Não na memória', borderwidth=2, relief="groove", width=30, height=2, bg='red')
            lbl.grid(row=i // 5, column=i % 5, padx=5, pady=5)
            self.page_labels[i] = lbl

        # Frames de memória física
        self.memory_labels = {}
        for i in range(MEM_FISICA_PAGINAS):
            lbl = tk.Label(self.tables_frame, text=f'Frame {i}: Vazio', borderwidth=2, relief="ridge", width=30, height=2, bg='lightgrey')
            lbl.grid(row=2 + i // 5, column=i % 5, padx=5, pady=5)
            self.memory_labels[i] = lbl

        # Mensagens de Log
        self.log_messages = tk.Text(self, height=8, width=80)
        self.log_messages.pack(pady=10)
        self.log_messages.config(state='disabled')

    def log(self, message):
        self.log_messages.config(state='normal')
        self.log_messages.insert(tk.END, message + '\n')
        self.log_messages.see(tk.END)
        self.log_messages.config(state='disabled')

    def acessar_pagina(self):
        pagina_virtual = random.randint(0, NUM_PAGINAS - 1)
        pagina_fisica = tabela_paginas[pagina_virtual]

        # Inicia o log com a página solicitada
        self.log(f'Solicitando acesso à página {pagina_virtual}.')

        # Simula um page fault
        if pagina_fisica is None:
            self.log(f'Page fault! Página {pagina_virtual} não está na memória.')
            try:
                pagina_fisica = memoria_fisica.index(None)
                self.log(f'Alocando frame {pagina_fisica} para a página {pagina_virtual}.')
            except ValueError:
                # Simulação simples de substituição de página (FIFO)
                pagina_fisica = memoria_fisica.index(min(memoria_fisica, key=lambda x: tabela_paginas[x] if x is not None else float('inf')))
                pagina_substituida = memoria_fisica[pagina_fisica]
                self.log(f'Substituindo página {pagina_substituida} no frame {pagina_fisica} pela página {pagina_virtual}.')

            # Atualiza a memória física
            old_page = memoria_fisica[pagina_fisica]
            memoria_fisica[pagina_fisica] = pagina_virtual
            tabela_paginas[pagina_virtual] = pagina_fisica
            if old_page is not None:
                tabela_paginas[old_page] = None

        else:
            self.log(f'Página {pagina_virtual} já está na memória no frame {pagina_fisica}.')

        # Atualiza a interface gráfica
        for pv, pf in tabela_paginas.items():
            color = 'green' if pf is not None else 'red'
            self.page_labels[pv].config(text=f'Página {pv}: {("Não na memória", f"Frame {pf}")[pf is not None]}', bg=color)
        for i in range(MEM_FISICA_PAGINAS):
            page = memoria_fisica[i]
            color = 'yellow' if page is not None else 'lightgrey'
            self.memory_labels[i].config(text=f'Frame {i}: {("Vazio", f"Página {page}")[page is not None]}', bg=color)

root = tk.Tk()
root.title("Simulador de Paginação de Memória")
app = Application(master=root)
app.mainloop()
