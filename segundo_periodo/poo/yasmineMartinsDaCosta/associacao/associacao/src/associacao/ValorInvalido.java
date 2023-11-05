package associacao;

public class ValorInvalido extends Exception{
    public ValorInvalido(){
        super("O valor inserido é inválido!");
    }
}
//indicando que algum dado de alguma entidade não foi completamente preenchido, tais como dados de um associado, dados de reunião, dados de taxa,
//São considerados não preenchidos strings vazias, valores nulos, e no caso de números, valor menores que zero. Tudo isso deveria gerar a exceção de ValorInvalido.