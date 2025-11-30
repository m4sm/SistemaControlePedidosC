# SistemaControlePedidosC

---

# 🗂️ Sistema de Controle de Pedidos (SCP)

Projeto desenvolvido em linguagem **C**, utilizando a biblioteca **ncurses**, para gerenciamento de **Clientes**, **Produtos** e **Pedidos**, com persistência de dados em arquivos `.csv`.
O sistema foi criado como parte da disciplina **Práticas de Programação** do curso de **Sistemas de Informação – Universidade Estadual de Goiás (UEG)**.

---

## 📌 Sumário

* [Descrição Geral](#-descrição-geral)
* [Funcionalidades](#-funcionalidades)

  * [Módulo Cliente](#-módulo-cliente)
  * [Módulo Produto](#-módulo-produto)
  * [Módulo Pedido](#-módulo-pedido)
* [Requisitos do Sistema](#-requisitos-do-sistema)
* [Arquitetura e Fluxo](#-arquitetura-e-fluxo)
* [Persistência de Dados](#-persistência-de-dados)
* [Autores](#-autores)

---

## 📖 Descrição Geral

O **Sistema de Controle de Pedidos (SCP)** tem como objetivo manipular e organizar cadastros de Clientes, Produtos e Pedidos.
A interface é construída em **ncurses**, permitindo navegação em modo texto, enquanto os dados são armazenados em arquivos `.csv` e carregados em memória utilizando **estruturas de dados tipo lista (arrays)**.

---

## 🧩 Funcionalidades

### 📁 Módulo Cliente

Responsável pela manipulação dos dados dos clientes (Pessoa Física ou Jurídica).

#### **Cadastrar Cliente**

Fluxo principal:

1. Usuário informa o **código identificador**.
2. Sistema verifica se o código já existe.
3. Usuário informa **CPF** (PF) ou **CNPJ** (PJ).
4. Sistema valida CPF/CNPJ conforme algoritmos da Receita Federal.
5. Sistema verifica duplicidade de CPF/CNPJ.
6. Usuário informa endereço, telefone e email.
7. Usuário informa:

   * Nome e celular (Pessoa Física), **ou**
   * Razão social e nome de contato (Pessoa Jurídica).
8. Cadastro é finalizado.

#### **Consultar Cliente**

* Usuário informa código → sistema exibe os dados se existir.

#### **Remover Cliente**

* Usuário informa código → sistema verifica → solicita confirmação → remove ou cancela.

#### **Listar Clientes**

* Exibe todos os clientes cadastrados com todas as informações.

---

### 📦 Módulo Produto

Manipulação de produtos comercializados pela empresa.

#### **Cadastrar Produto**

1. Usuário informa código do produto.
2. Sistema verifica duplicidade.
3. Usuário informa descrição, preço e quantidade.
4. Produto é salvo.

#### **Consultar Produto**

* Usuário informa código → sistema mostra os dados.

#### **Remover Produto**

* Sistema verifica se:

  * Produto existe.
  * Produto está vinculado a algum pedido (se sim, não permite remoção).
* Solicita confirmação.
* Remove ou cancela.

#### **Listar Produtos**

* Exibe todos os produtos cadastrados.

---

### 🧾 Módulo Pedido

Processo completo de criação e gerenciamento dos pedidos.

#### **Cadastrar Pedido**

1. Usuário informa o código do pedido.
2. Sistema verifica duplicidade.
3. Usuário informa o código do cliente.
4. Sistema verifica se o cliente existe.
5. Para cada item do pedido:

   * Usuário informa o código do produto.
   * Sistema verifica se o produto existe.
   * Usuário informa quantidade.
6. Itens são associados ao pedido.
7. Pedido é finalizado.

A relação entre Pedido e Produto é tratada por meio da struct **ItemPedido**, responsável por armazenar:

* Código do produto
* Quantidade
* Subtotal

#### **Consultar Pedido**

* Exibe todos os itens, valores e dados associados.

#### **Remover Pedido**

* Verifica existência → exclui o pedido e seus itens.

#### **Listar Pedidos**

* Lista todos os pedidos cadastrados.

---

## ⚙️ Requisitos do Sistema

* Linguagem **C**
* Biblioteca **ncurses** para interface em modo texto
* Arquivos `.csv`:

  * `Clientes.csv`
  * `Produtos.csv`
  * `Pedidos.csv`

---

## 🗃️ Persistência de Dados

Ao iniciar o sistema:

* Todos os dados são **carregados em memória** em listas (arrays).
* Todas as operações (Cadastrar, Consultar, Remover, Listar) trabalham **somente em memória**.

Ao encerrar:

* Todos os dados são **salvos novamente** nos arquivos `.csv`
* Os arquivos são **sobrescritos** com o estado atual das listas.

---

## 🔄 Arquitetura e Fluxo do Sistema

1. Um **Cliente** realiza um **Pedido**.
2. O Pedido contém **um ou mais Itens de Pedido**.
3. Cada Item de Pedido representa:

   * Um Produto
   * Uma quantidade
   * Um subtotal calculado

A estrutura `ItemPedido` resolve a relação muitos-para-muitos entre Pedido e Produto.

---

## 👥 Autores

* **Marco Antonio Sousa Miranda** – Sistemas de Informação – Universidade Estadual de Goiás
* **Arthur Almeida Borges** – Sistemas de Informação – Universidade Estadual de Goiás
* **Rodrigo Ribeiro de Almeida** – Sistemas de Informação – Universidade Estadual de Goiás

---



