class Node {
    constructor(value) {
      this.value = value;
      this.left = null;
      this.right = null;
    }
  }
  
  class BinarySearchTree {
    constructor() {
      this.root = null;
    }
  
    insert(value) {
      const newNode = new Node(value);
  
      if (!this.root) {
        this.root = newNode;
        return this;
      }
  
      let current = this.root;
  
      while (true) {
        if (value === current.value) {
          return undefined; // Evita inserção de valores duplicados
        }
  
        if (value < current.value) {
          if (!current.left) {
            current.left = newNode;
            return this;
          }
          current = current.left;
        } else {
          if (!current.right) {
            current.right = newNode;
            return this;
          }
          current = current.right;
        }
      }
    }
  
    find(value) {
      if (!this.root) {
        return false;
      }
  
      let current = this.root;
      let found = false;
  
      while (current && !found) {
        if (value === current.value) {
          found = true;
        } else if (value < current.value) {
          current = current.left;
        } else {
          current = current.right;
        }
      }
  
      return found;
    }
  
    size(node = this.root) {
      if (!node) {
        return 0;
      }
      return 1 + this.size(node.left) + this.size(node.right);
    }
  
    height(node = this.root) {
      if (!node) {
        return -1;
      }
      const leftHeight = this.height(node.left);
      const rightHeight = this.height(node.right);
      return 1 + Math.max(leftHeight, rightHeight);
    }
  
    findMin() {
      let current = this.root;
      while (current.left) {
        current = current.left;
      }
      return current.value;
    }
  
    findMax() {
      let current = this.root;
      while (current.right) {
        current = current.right;
      }
      return current.value;
    }
    inOrderTraversal(node = this.root) {
    if (!node) {
      return [];
    }
    return [...this.inOrderTraversal(node.left), node.value, ...this.inOrderTraversal(node.right)];
  }

  postOrderTraversal(node = this.root) {
    if (!node) {
      return [];
    }
    return [...this.postOrderTraversal(node.left), ...this.postOrderTraversal(node.right), node.value];
  }

  preOrderTraversal(node = this.root) {
    if (!node) {
      return [];
    }
    return [node.value, ...this.preOrderTraversal(node.left), ...this.preOrderTraversal(node.right)];
  }

  levelOrderTraversal() {
    const result = [];
    const queue = [];

    if (this.root) {
      queue.push(this.root);
    }

    while (queue.length > 0) {
      const current = queue.shift();
      result.push(current.value);

      if (current.left) {
        queue.push(current.left);
      }
      if (current.right) {
        queue.push(current.right);
      }
    }

    return result;
  }
  inOrderTraversal(node = this.root) {
    if (!node) {
      return [];
    }
    return [...this.inOrderTraversal(node.left), node.value, ...this.inOrderTraversal(node.right)];
  }

  postOrderTraversal(node = this.root) {
    if (!node) {
      return [];
    }
    return [...this.postOrderTraversal(node.left), ...this.postOrderTraversal(node.right), node.value];
  }

  preOrderTraversal(node = this.root) {
    if (!node) {
      return [];
    }
    return [node.value, ...this.preOrderTraversal(node.left), ...this.preOrderTraversal(node.right)];
  }

  levelOrderTraversal() {
    const result = [];
    const queue = [];

    if (this.root) {
      queue.push(this.root);
    }

    while (queue.length > 0) {
      const current = queue.shift();
      result.push(current.value);

      if (current.left) {
        queue.push(current.left);
      }
      if (current.right) {
        queue.push(current.right);
      }
    }

    return result;
  }
  internalPathLength(node = this.root, depth = 0) {
    if (!node) {
      return 0;
    }

    return depth + this.internalPathLength(node.left, depth + 1) + this.internalPathLength(node.right, depth + 1);
  }
  isBalanced(node = this.root) {
    if (!node) {
      return true;
    }

    const leftHeight = this.height(node.left);
    const rightHeight = this.height(node.right);
    
    if (Math.abs(leftHeight - rightHeight) <= 1 && this.isBalanced(node.left) && this.isBalanced(node.right)) {
      return true;
    }

    return false;
  }
}
  
  


    const svg = document.getElementById('tree-svg');
    const sizeElement = document.getElementById('size');
    const heightElement = document.getElementById('height');
    const minElement = document.getElementById('min');
    const maxElement = document.getElementById('max');
    const inOrderElement = document.getElementById('in-order');
    const postOrderElement = document.getElementById('post-order');
    const preOrderElement = document.getElementById('pre-order');
    const levelOrderElement = document.getElementById('level-order');
    const nameInput = document.getElementById('name-input');
    const insertButton = document.getElementById('insert-button');
    const internalPathLengthElement = document.getElementById('internal-path-length');
    const isBalancedElement = document.getElementById('is-balanced');

    const tree = new BinarySearchTree();

    function updateUI() {
      sizeElement.textContent = tree.size();
      heightElement.textContent = tree.height();
      minElement.textContent = tree.findMin();
      maxElement.textContent = tree.findMax();
      inOrderElement.textContent = tree.inOrderTraversal().join(', ');
      postOrderElement.textContent = tree.postOrderTraversal().join(', ');
      preOrderElement.textContent = tree.preOrderTraversal().join(', ');
      levelOrderElement.textContent = tree.levelOrderTraversal().join(', ');
      internalPathLengthElement.textContent = tree.internalPathLength();
      isBalancedElement.textContent = tree.isBalanced() ? 'Sim' : 'Não';
      

      // Limpa e reconstrói a exibição da árvore
      svg.innerHTML = '';
      const treeHeight = tree.height();
      const treeWidth = Math.pow(2, treeHeight) * 40;
      displayTree(tree.root, treeWidth / 2, 20, treeWidth / 4, 1);
    }

    function displayTree(node, x, y, dx, dy) {
      if (node) {
        const circle = document.createElementNS("http://www.w3.org/2000/svg", "circle");
        circle.setAttribute("cx", x);
        circle.setAttribute("cy", y);
        circle.setAttribute("r", 10);
        circle.setAttribute("fill", "white");
        circle.setAttribute("stroke", "black");
        svg.appendChild(circle);
        
        const text = document.createElementNS("http://www.w3.org/2000/svg", "text");
        text.setAttribute("x", x);
        text.setAttribute("y", y + 3);
        text.setAttribute("text-anchor", "middle");
        text.setAttribute("font-size", "12");
        text.textContent = node.value;
        svg.appendChild(text);
        
        if (node.left) {
          const line = document.createElementNS("http://www.w3.org/2000/svg", "line");
          line.setAttribute("x1", x);
          line.setAttribute("y1", y + 10);
          line.setAttribute("x2", x - dx);
          line.setAttribute("y2", y + 20 * dy);
          line.setAttribute("stroke", "black");
          svg.appendChild(line);
          displayTree(node.left, x - dx, y + 20 * dy, dx / 2, dy + 1);
        }
        
        if (node.right) {
          const line = document.createElementNS("http://www.w3.org/2000/svg", "line");
          line.setAttribute("x1", x);
          line.setAttribute("y1", y + 10);
          line.setAttribute("x2", x + dx);
          line.setAttribute("y2", y + 20 * dy);
          line.setAttribute("stroke", "black");
          svg.appendChild(line);
          displayTree(node.right, x + dx, y + 20 * dy, dx / 2, dy + 1);
        }
      }
    }

    insertButton.addEventListener('click', () => {
      const name = nameInput.value;
      if (name.trim() !== '') {
        tree.insert(name);
        nameInput.value = '';
        updateUI();
      }
    });

    updateUI();