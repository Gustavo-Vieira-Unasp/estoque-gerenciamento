#include "categoria.h"
#include <string.h>
#include <stdio.h>

//Permite a seleção de categoria
const char* getNomeCategoria(Categoria categoria){
    switch (categoria){
    case CATEGORIA_ALIMENTOS: return "Alimentos";
    case CATEGORIA_BEBIDAS: return "Bebidas";
    case CATEGORIA_CONSTRUCAO: return "Construcao";
    case CATEGORIA_ELETRONICOS: return "Eletronicos";
    case CATEGORIA_LIMPEZA: return "Limpeza";
    case CATEGORIA_MEDICAMENTOS: return "Medicamentos";
    default: return "Categoria Desconhecida";
    }
}