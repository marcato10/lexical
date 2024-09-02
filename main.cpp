#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip> // Necessário para std::setw
#include <iostream>
#include <sstream>
#include <stdexcept> // Para runtime_error
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Token
struct Token {
    string lexema;
    string simbolo;
};

static const std::unordered_map<std::string, std::string> symbolMap = {
        {"programa", "sprograma"},
        {"inicio", "sinicio"},
        {"fim", "sfim"},
        {"procedimento", "sprocedimento"},
        {"funcao", "sfuncao"},
        {"se", "sse"},
        {"entao", "sentao"},
        {"senao", "ssenao"},
        {"enquanto", "senquanto"},
        {"faca", "sfaca"},
        {":=", "satribuicao"},
        {"escreva", "sescreva"},
        {"leia", "sleia"},
        {"var", "svar"},
        {"inteiro", "sinteiro"},
        {"booleano", "sbooleano"},
        {"identificador", "sidentificador"},
        {"numero", "snumero"},
        {".", "sponto"},
        {";", "sponto_virgula"},
        {",", "svirgula"},
        {"(", "sabre_parenteses"},
        {")", "sfecha_parenteses"},
        {">", "smaior"},
        {">=", "smaiorig"},
        {"=", "sig"},
        {"<", "smenor"},
        {"<=", "smenorig"},
        {"!=", "sdif"},
        {"+", "smais"},
        {"-", "smenos"},
        {"*", "smult"},
        {"div", "sdiv"},
        {"e", "se"},
        {"ou", "sou"},
        {"nao", "snao"},
        {":", "sdoispontos"},
        {"verdadeiro", "sverdadeiro"},
        {"falso", "sfalso"}};

const std::string &getSymbolByKey(const std::string &key) {
    return symbolMap.find(key) != symbolMap.end() ? symbolMap.at(key)
                                                  : symbolMap.at("identificador");
}

vector<Token> tokens;

std::string lerArquivo(const string &path) {
    ifstream arquivo(path, ios::binary | ios::ate);

    if (!arquivo.is_open()) {
        throw runtime_error("Não foi possível abrir o arquivo.");
    }

    // Obter o tamanho do arquivo
    streamsize tamanho = arquivo.tellg();
    arquivo.seekg(0, ios::beg);

    std::stringstream buffer;
    buffer << arquivo.rdbuf();

    // Cria uma com o tamanho do arquivo
    std::string conteudo = buffer.rdbuf()->str();

    return conteudo;
}

int trata_digito(int i, const std::string &arquivo) {
    Token token;
    string num;
    num += arquivo[i];
    i++;

    while (isdigit(arquivo[i])) {
        num += arquivo[i];
        i++;
    }

    token.lexema = num;
    token.simbolo = "snumero";
    tokens.push_back(token);

    return i;
}

int trata_letra(int i, const std::string &arquivo) {
    Token token;
    string id;
    id += arquivo[i];
    i++;
    while (isalpha(arquivo[i]) || arquivo[i] == '_') {
        id += arquivo[i];
        i++;
    }

    token.lexema = id;
    token.simbolo = getSymbolByKey(token.lexema);

    tokens.push_back(token);
    return i;
}

int atribuicao(int i, const std::string &arquivo) {
    Token token;
    if (arquivo[i + 1] == '=') {
        token.lexema = ":=";
        token.simbolo = "satribuicao";
        i += 2;
    } else {
        token.lexema = ':';
        token.simbolo = "sdoispontos";
        i += 1;
    }
    tokens.push_back(token);
    return i;
}

int operador_aritmetico(int i, const std::string &arquivo) {
    Token token;

    // Converte o caracter em uma string
    std::string current(1, arquivo[i]);

    token.lexema = current;
    token.simbolo = getSymbolByKey(current);

    i++;
    tokens.push_back(token);
    return i; // Lê o próximo token.
}

int operador_relacional(int i, const std::string &arquivo) {
    Token token;

    if (arquivo[i] == '!') {
        if (arquivo[i + 1] == '=') {
            token.simbolo = "sdif";
            token.lexema = "!=";
            i += 2;
        } else {
            cout << "Erro '!' espera = em seguida..." << endl;
        }
    } else if (arquivo[i] == '<') {
        if (arquivo[i + 1] == '=') {
            token.simbolo = "smenorig";
            token.lexema = "<=";
            i += 2;
        } else {
            token.simbolo = "smenor";
            token.lexema = '<';
            i++;
        }
    } else if (arquivo[i] == '>') {
        if (arquivo[i + 1] == '=') {
            token.simbolo = "smaiorig";
            token.lexema = ">=";
            i += 2;
        } else {
            token.simbolo = "smaior";
            token.lexema = '>';
            i++;
        }
    }

    else {
        token.lexema = '=';
        token.simbolo = "sig";
        i++;
    }
    tokens.push_back(token);
    return i;
}

int pontuacao(int i, const std::string &arquivo) {
    Token token;
    // Converte o caracter em uma string
    std::string current(1, arquivo[i]);

    token.lexema = current;
    token.simbolo = getSymbolByKey(current);

    tokens.push_back(token);
    i++;
    return i;
}

int pega_token(int index, const std::string &arquivo) {
    char carac = arquivo[index];
    if (isdigit(carac)) {
        index = trata_digito(index, arquivo);
        return index;
    } else if (isalpha(carac)) {
        index = trata_letra(index, arquivo);
        return index;
    } else if (carac == ':') {
        index = atribuicao(index, arquivo);
        return index;
    } else if (carac == '+' || carac == '-' || carac == '*') {
        index = operador_aritmetico(index, arquivo);
        return index;
    } else if (carac == '!' || carac == '<' || carac == '>' || carac == '=') {
        index = operador_relacional(index, arquivo);
        return index;
    } else if (carac == ';' || carac == ',' || carac == '(' || carac == ')' ||
               carac == '.') {
        index = pontuacao(index, arquivo);
        return index;
    } else {
        cout << "Caractere inválido" << carac << endl;
        return index + 1;
    }
}

void lexical(const std::string &arquivo) {
    int i = 0;

    cout << "EOF:" << arquivo.at(arquivo.size() - 1) << endl;
    bool comentario = false;
    std::cout << arquivo.size() << std::endl;
    while (i < arquivo.size() + 1) {
        if (arquivo[i] == '{') {
            comentario = true;
        } else if (arquivo[i] == '}') {
            comentario = false;
            i++; // Avança para o próximo caractere após o comentário

            continue;
        }

        if (!comentario) {
            if (isspace(
                    arquivo[i])) { // Ignora espaços, quebras de linha e tabulações
                i++;
                continue;
            } else {
                i = pega_token(i, arquivo);
            }
        } else {
            i++; // Avança dentro do comentário
        }
    }
}

void visualizarTokens(const vector<Token> &tokens) {
    // Definir a largura das colunas
    const int larguraLexema = 20;
    const int larguraSimbolo = 20;

    // Cabeçalho da tabela
    cout << left << setw(larguraLexema) << "Lexema" << setw(larguraSimbolo)
         << "Símbolo" << endl;
    cout << setfill('-') << setw(larguraLexema + larguraSimbolo) << ""
         << setfill(' ') << endl;

    // Conteúdo da tabela
    for (const auto &token : tokens) {
        cout << left << setw(larguraLexema) << token.lexema << setw(larguraSimbolo)
             << token.simbolo << endl;
    }
}

int main(int argc, char *argv[]) {
    std::string path;
    if (argc != 2) {
        std::cout << "Using default path" << std::endl;
        path =
                std::string(std::filesystem::current_path().string() + "/Source.txt");
    } else
        path = argv[1];

    // Função que lê o conteúdo de um arquivo e retorna um vetor de caracteres
    std::string arquivo = lerArquivo(path);

    lexical(arquivo);
    visualizarTokens(tokens);
    return EXIT_SUCCESS;
}