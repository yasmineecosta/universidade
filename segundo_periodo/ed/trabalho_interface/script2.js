// class Node{
//     constructor(nome){
//         this.nome = nome;
//         this.left = null;
//         this.right = null;
//         this.parent = null;
//         this.level = 0;
//         // this.xy = {x:0,y:0};
//     }

//     heightTillRoot(){
//         let h = 0;
//         let current_node = this;
//         while(current_node.parent !== null){
//             h++;
//             current_node = current_node.parent;
//         }
//         console.log(h);
//         return h - 1;
//     }
// }

// class BinaryTree{
//     constructor(){
//         this.root = null;
//         this.n = 0;
//     }

//     insert(nome){
//         const newNode = new Node(nome);

//         if(!this.root){
//             this.root = newNode;
//             return;
//         }
//         this.insertNode(this.root, newNode);
//     }

//     insertNode(node, newNode){
//         if(newNode.nome < node.nome){
//             if(!node.left){
//                 node.left = newNode;
//                 newNode.parent = node;
//                 newNode.level = node.level + 1;
//             }else{
//                 this.insertNode(node.left, newNode);
//             }
//         }else{
//             if(!node.right){
//                 node.right = newNode;
//                 newNode.parent = node;
//                 newNode.level = node.level + 1;
//             }else{
//                 this.insertNode(node.right, newNode);
//             }
//         }
//     }

//     search(nome){
//         return this.searchNode(this.root, nome);
//     }

//     searchNode(node, nome){
//         if(!node){
//             return null;
//             // return false;
//         }
//         if(node.nome === nome){
//             return node;
//             // return true;
//         }
//         else if(nome < node.nome){
//             return this.searchNode(node.left, nome);
//         }else{
//             return this.searchNode(node.right, nome);
//         }
//     }

// }



// const infoButton = document.getElementById('infoBtn');
// const traversalsButton = document.getElementById('traversalsBtn');
// const screenDiv = document.getElementById('screenDiv');

// infoButton.addEventListener('click', () => {
//     document.querySelector('.informacoes').style.display = 'flex';
//     screenDiv.style.display = 'none';
// });

// traversalsButton.addEventListener('click', () => {
//     screenDiv.style.display = 'block';
//     document.querySelector('.informacoes').style.display = 'none';
// });

// const closeBtn = document.getElementById('closeBtn');
// closeBtn.addEventListener('click', () => {
//     screenDiv.style.display = 'none';
// });

class Node {
    constructor(name) {
        this.name = name;
        this.left = null;
        this.right = null;
    }
}

class BinaryTree {
    constructor() {
        this.root = null;
    }

    insert(name) {
        const newNode = new Node(name);

        if (!this.root) {
            this.root = newNode;
            return;
        }

        this._insertNode(this.root, newNode);
    }

    _insertNode(node, newNode) {
        if (newNode.name < node.name) {
            if (!node.left) {
                node.left = newNode;
            } else {
                this._insertNode(node.left, newNode);
            }
        } else {
            if (!node.right) {
                node.right = newNode;
            } else {
                this._insertNode(node.right, newNode);
            }
        }
    }

    getHeight(node) {
        if (!node) return -1;
        return 1 + Math.max(this.getHeight(node.left), this.getHeight(node.right));
    }

    getSize(node) {
        if (!node) return 0;
        return 1 + this.getSize(node.left) + this.getSize(node.right);
    }

    getMin(node) {
        if (!node) return null;
        while (node.left) {
            node = node.left;
        }
        return node.name;
    }

    getMax(node) {
        if (!node) return null;
        while (node.right) {
            node = node.right;
        }
        return node.name;
    }

    inOrderTraversal(node, callback) {
        if (node) {
            this.inOrderTraversal(node.left, callback);
            callback(node.name);
            this.inOrderTraversal(node.right, callback);
        }
    }
}

// Elementos HTML
const insertButton = document.getElementById('insertBtn');
const addBtn = document.getElementById('addBtn');
const nameInput = document.getElementById('nameInput');
const infoAltura = document.getElementById('infoAltura');
const infoTamanho = document.getElementById('infoTamanho');
const infoMenor = document.getElementById('infoMenor');
const infoMaior = document.getElementById('infoMaior');
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
ctx.fillStyle = 'blue';
ctx.font = '15px Arial';
ctx.textAlign = 'center';

const tree = new BinaryTree();

// Event listeners
addBtn.addEventListener('click', () => {
    const name = nameInput.value;
    if (name.trim() !== '') {
        tree.insert(name);
        drawTreeOnCanvas();
        nameInput.value = '';
    }
});

function drawTree(node, x, y, xOffset) {
// function drawTree(node, x, y, xOffset, isMainNode = true) {    
    if (!node) return;

    const radius = 20;
    // const radius = isMainNome ? 30 : 20;
    ctx.beginPath();
    ctx.arc(x, y, radius, 0, Math.PI * 2);
    ctx.stroke();
    ctx.fillText(node.name, x - 5, y + 5);
    // ctx.fillText(node.name, x, y + 6);
    // ctx.fillStyle = isMainNode ? '#28ede7' : 'blue';
    // ctx.font = isMainNode ? 'bold 18px Arial' : '15px Arial';
    // ctx.textAlign = 'center';

    if (node.left) {
        const leftX = x - xOffset;
        const leftY = y + 50;
        // const leftY = y + 60;
        ctx.beginPath();
        ctx.moveTo(x, y + radius);
        ctx.lineTo(leftX, leftY - radius);
        ctx.stroke();
        drawTree(node.left, leftX, leftY, xOffset / 2);
        // drawTree(node.left, leftX, leftY, xOffset / 2, false);

    }

    if (node.right) {
        const rightX = x + xOffset;
        const rightY = y + 50;
        ctx.beginPath();
        ctx.moveTo(x, y + radius);
        ctx.lineTo(rightX, rightY - radius);
        ctx.stroke();
        drawTree(node.right, rightX, rightY, xOffset / 2);
    }
}

function drawTreeOnCanvas() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawTree(tree.root, canvas.width / 2, 50, 200);
}

insertButton.addEventListener('click', () => {
    const altura = tree.getHeight(tree.root);
    const tamanho = tree.getSize(tree.root);
    const menorElemento = tree.getMin(tree.root);
    const maiorElemento = tree.getMax(tree.root);

    infoAltura.textContent = `Altura: ${altura}`;
    infoTamanho.textContent = `Tamanho: ${tamanho}`;
    infoMenor.textContent = `Menor elemento: ${menorElemento}`;
    infoMaior.textContent = `Maior elemento: ${maiorElemento}`;
});
