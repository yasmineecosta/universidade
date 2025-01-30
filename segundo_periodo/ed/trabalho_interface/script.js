class Node {
    constructor(nome) {
      this.nome = nome;
      this.left = null;
      this.right = null;
      this.parent = null;
      this.level = 0;
      this.xy = { x: 0, y: 0 };
    }
  
    heightTillRoot() {
      let h = 0;
      let current_node = this;
      while (current_node.parent !== null) {
        h++;
        current_node = current_node.parent;
      }
      console.log(h);
      return h - 1;
    }
  }
  
  function equalsStrings(str1, str2) {
    str1 = str1.toLowerCase();
    str2 = str2.toLowerCase();
  
    return str1.localeCompare(str2) === 0;
  }
  
  class BinaryTree {
    constructor() {
      this.root = null;
      this.n = 0;
    }
  
    insert(nome) {
      const newNode = new Node(nome);
      this.n++;
      if (this.root === null) {
        this.root = newNode;
        this.root.xy = { x: 0, y: 0 };
      } else {
        this.insertNode(this.root, newNode);
      }
    }
  
    insertNode(node, newNode) {
      if (equalsStrings(newNode.nome, node.nome) < 0) {
        if (node.left === null) {
          node.left = newNode;
          newNode.level = node.level + 1;
          newNode.parent = node;
          // newNode.xy.x = node.xy.x*2;
          // newNode.xy.y = newNode.level;
          newNode.xy = { x: node.xy.x * 2, y: newNode.level };
        } else {
          this.insertNode(node.left, newNode);
        }
      } else {
        if (node.right === null) {
          node.right = newNode;
          newNode.level = node.level + 1;
          newNode.parent = node;
          // newNode.xy.x = node.xy.x*2 + 1;
          // newNode.xy.y = newNode.level;
          newNode.xy = { x: node.xy.x * 2 + 1, y: newNode.level };
        } else {
          this.insertNode(node.right, newNode);
        }
      }
    }
  
    search(nome) {
      let current_node = this.root;
  
      while (current_node !== null) {
        if (equalsStrings(nome, current_node.nome) === 0) {
          return current_node;
        } else if (equalsStrings(nome, current_node.nome) < 0) {
          current_node = current_node.left;
        } else {
          current_node = current_node.right;
        }
      }
      return null; //nome não encontrado
    }
  
    tree_height(current_node = this.root) {  ///
      if (current_node === null) {
        return 0;
      }
      let leftHeight = this.tree_heigth(root.left);
      let rightHeight = this.tree_heigth(root.right);
  
      // return Math.max(leftHeight, rightHeight) + 1;
  
      if (leftHeight < rightHeight) {
        return (leftHeight + 1);
      } else {
        return (rightHeight + 1);
      }
    }
  
    InternLength(){
      if(this.root === null){
        return 0;
      }
  
      let comprimentos = 0;
      let currentLevel = 0;
      let fila = [{node: this.root, level: 0}];
  
      while(fila.length > 0){
        const {node, level} = fila.shift();
  
        if(currentLevel !== level){
          currentLevel = level;
        }
  
        if(node.left !== null){
          fila.push({node: node.left, level: level + 1});
          InternLength += level + 1;
        }
  
        if(node.right !== null){
          fila.push({node: node.right, level: level + 1});
          InternLength += level + 1;
        }
      }
      return InternLength;
    }
    
    minValue(node) {
      if (node.root === null) {
        return -1;
      }
      let min_value = node.nome;
  
      while (node.left !== null) {
        min_value = node.left.nome;
        node = node.left;
      }
      return min_value;
    }
  
    maxValue(node) {
      if (node.root === null) {
        return -1;
      }
      let max_value = node.nome;
  
      while (node.right !== null) {
        max_value = node.left.nome;
        node = node.left;
      }
      return max_value;
    }
  
    treeSequence(tree){
      let result = [];
  
      if(tree.root === null){
        return result;
      }
  
      let fila = [tree.root];
  
      while(fila.length > 0){
        let currentNode = fila.shift();
        result.push(currentNode);
  
        if(currentNode.left !== null){
          fila.push(currentNode.left);
        }
  
        if(currentNode.right !== null){
          fila.push(currentNode.right);
        }
      }
      return result;
    }
    
    in_order(node = this.root, result = "") {
      if (node !== null) {
        result = this.in_order(node.left, result);
        result += node.nome + " -> ";
        result = this.in_order(node.right, result);
      }
      return result;
    }
  
    pre_order(node = this.root, result = "") {
      if (node !== null) {
        result += node.nome + " -> ";
        result = this.pre_order(node.left);
        result = this.pre_order(node.right);
      }
      return result;
    }
  
    post_order(node = this.root, result = "") {
      if(node !== null){
        result = post_order(node.left);
        result = post_order(node.right);
        result += node.nome + " -> "
      }
      return result;
    }
  
    levelOrdem(){
      let result = [];
      function visit(node, level){
        if(!node){
          return;
        }
  
        if(!result[level]){
          result[level] = [];
        }
  
        result[level].push(node.nome);
  
        visit(node.left, level+1);
        visit(node.right, level+1);
      }
  
      visit(this.root, 0);
  
      return result
        .map((level) => level.join(" ->"))
        .filter((level) => level !== "")
        .join(" ->");
    }
  }
  
  function xyTransform(origin, xy){
    if(xy.x === 0 && xy.y === 0){
      return origin;
    }
  
    let x1 = ((origin.x)/2**(xy.y)+((origin.x)/2**(xy.y-1))*(xy.x));
    let y1 = ((origin.y)+2*(origin.y)*(origin.y));
  
    return {x:x1, y:y1};
  }
  
  function xyParent(xy){
    let x = ((xy.x) - ((xy.x)%2)) / 2;
    let y = xy.y-1;
  
    return {x: x, y: y};
  }
  
  let tree = new BinaryTree();
  
  document.querySelector('.input').addEventListener('submit', (event) => {
    event.preventDefault();
    let val = document.querySelector('#Input').value;
    if(tree.search(val) != null){
        return;
    }
    console.log(val);
    tree.insert(val);
    var canvas = document.getElementById("canvas");
    width=canvas.width;
    var ctx = canvas.getContext('2d');
    ctx.fillStyle = 'green'
    ctx.font = '15px serif';
    xy_sequence = tree.treeSequence(tree);
    console.log(xy_sequence);
    r = 30;
    const origin = {x : width/2,y : r};
    for(var i = 0; i<xy_sequence.length;i++){
      let coordenadas_px = transformarCoordenadas(origem,sequencia_coord[i].coordenada)
      ctx.beginPath();
      ctx.moveTo(coordenadas_px.x+raio,coordenadas_px.y);
      ctx.arc(coordenadas_px.x, coordenadas_px.y, raio, 0, Math.PI * 2, true);
      ctx.fill();
      ctx.stroke();
      ctx.strokeText(sequencia_coord[i].valor, coordenadas_px.x-raio,coordenadas_px.y )
      if(i == 0) continue;
      coordenada_pai = PegarCoordenadaDoPai(sequencia_coord[i].coordenada);
      let coordenada_pai_px = transformarCoordenadas(origem,coordenada_pai);
      ctx.moveTo(coordenadas_px.x,coordenadas_px.y);
      ctx.lineTo(coordenada_pai_px.x,coordenada_pai_px.y);
      ctx.stroke();
      //ctx.strokeText(sequencia_coord[i].valor, coordenadas_px.x-raio,coordenadas_px.y );
    }
    ctx.stroke();
  });
  const botoes = document.querySelectorAll('.meuBotao');
  let resposta = document.querySelector('.resposta');
  const tituloExibido = document.querySelector('.tituloResposta');
  const minhaTela = document.querySelector('#minhaTela');
  const botaoFechar = document.querySelector('#botaoFechar');
  
  
  botoes.forEach(function(botao) {
    botao.addEventListener('click', function() {
      console.log(botao);
      minhaTela.style.display = 'block';
      document.querySelector('.botoesTravessia').style.display='none';
      const texto = botao.getAttribute('data-texto');
      switch (texto) {
        case 'Inserir':
          canvas.style.display='none';
          resposta.innerHTML = ` Insira um nome:`;
          document.querySelector('.entrada').style.display='inline';  
          break;
          case 'Tamanho da arvore':
          canvas.style.display='none';
          resposta.innerHTML = ` ${arvore.n} nós`;
          document.querySelector('.entrada').style.display='none';
          break;
          case 'Altura da arvore':
            canvas.style.display='none';
            resposta.innerHTML = `${arvore.altura()}`;
            document.querySelector('.entrada').style.display='none';
            break;
            case 'Menor Elemento':  
            canvas.style.display='none';
            resposta.innerHTML = `${arvore.pegarMinimo().valor}`;
            document.querySelector('.entrada').style.display='none';
            break;
            case 'Maior Elemento':  
              canvas.style.display='none';
              resposta.innerHTML = `${arvore.pegarMaximo().valor}`;
              document.querySelector('.entrada').style.display='none';
              break;
          case 'Comprimento Interno':  
            canvas.style.display='none';
            resposta.innerHTML = `${arvore.comprimentoInterno()}`;
            document.querySelector('.entrada').style.display='none';
            break;
          case 'Travessias':  
            canvas.style.display='none';
            resposta.innerHTML = '';
            document.querySelector('.botoesTravessia').style.display='flex';
            document.querySelector('.entrada').style.display='none';
            break;
      }
      tituloExibido.textContent = texto;
    });
  });
  
  botaoFechar.addEventListener('click', function() {
    minhaTela.style.display = 'none';
    canvas.style.display='inline'
  });
  
  const botoesTravs = document.querySelectorAll('.butaoTravessia');
  
  
  botoesTravs.forEach(function(botao){
    botao.addEventListener('click', function() {
      const travessia =botao.getAttribute('data-texto');
      switch (travessia) {
        case 'Em Ordem':
          document.querySelector('.botoesTravessia').style.display='none';
          resposta.innerHTML = `${arvore.emOrdem()}`;
          break;
        case 'Pré-Ordem':
          document.querySelector('.botoesTravessia').style.display='none';
          resposta.innerHTML = `${arvore.preOrdem()}`;
          break;
        case 'Pós-Ordem':
          document.querySelector('.botoesTravessia').style.display='none';
          resposta.innerHTML = `${arvore.posOrdem()}`;
          break;
        case 'Level-Ordem':
          document.querySelector('.botoesTravessia').style.display='none';
          resposta.innerHTML = `${arvore.levelOrdem()}`;
          break;
      
        default:
          break;
      }  
      tituloExibido.textContent = travessia;
  })
  })
  
  