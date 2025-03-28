#include <iostream>
using namespace std;

// Cấu trúc của một nút trong cây tổng quát
struct Node {
    int data; // Dữ liệu của nút
    Node* firstChild; // Con đầu tiên của nút
    Node* nextSiblings; // Anh em cùng cấp của nút

    // Hàm khởi tạo nút mới
    Node(int x) {
        data = x;
        firstChild = nullptr;
        nextSiblings = nullptr;
    }
};

class Tree {
public:
    Node* root = nullptr; // Con trỏ gốc của cây

    // Hàm tìm cha của một nút trong cây
    Node* findParent(Node* root, int value) {
        if(root == nullptr){
            return nullptr; // Nếu cây rỗng, trả về nullptr
        }
        if(root->data == value){
            return root; // Nếu tìm thấy nút có giá trị cần tìm, trả về nút đó
        }
        // Tìm kiếm trong cây con
        Node* found = findParent(root->firstChild, value);
        if(found){
            return found; // Nếu tìm thấy trong cây con, trả về nút đó
        }
        // Nếu không tìm thấy trong cây con, tiếp tục tìm trong anh em cùng cấp
        return findParent(root->nextSiblings, value);
    }

    // Hàm tạo cây
    void makeTree(int x, int y) {
        if(root == nullptr) {
            // Nếu cây chưa có gốc, tạo nút gốc
            root = new Node(x);
        }
        // Tìm nút cha trong cây
        Node* parent = findParent(root, x);
        if(!parent){
            return; // Nếu không tìm thấy cha, bỏ qua
        }

        Node* newChild = new Node(y); // Tạo một nút con mới

        if(parent->firstChild == nullptr){
            parent->firstChild = newChild; // Nếu cha chưa có con, gán newChild làm con đầu tiên
        } else {
            // Nếu cha đã có con, tìm anh em cuối cùng để thêm vào danh sách
            Node* sibling = parent->firstChild;
            while(sibling->nextSiblings != nullptr) {
                sibling = sibling->nextSiblings;
            }
            sibling->nextSiblings = newChild;
        }
    }

    // Hàm tính chiều cao của cây
    int findHeight(Node* root) {
        if(root == nullptr){
            return -1; // Cây rỗng có chiều cao -1
        }

        int maxHeight = -1; // Chiều cao lớn nhất của các cây con

        Node* child = root->firstChild;
        while(child){
            // Tìm chiều cao lớn nhất của các con
            maxHeight = max(maxHeight, findHeight(child));
            child = child->nextSiblings;
        }
        return 1 + maxHeight; // Trả về chiều cao của cây
    }

    // Hàm in chiều cao của cây
    void printHeight() {
        cout << findHeight(root) << endl;
    }

    // Duyệt cây theo preOrder
    void preOrder(Node* root) {
        if(root == nullptr){
            return;
        }
        cout << root->data << " "; // In dữ liệu của nút hiện tại
        preOrder(root->firstChild); // Duyệt cây con
        preOrder(root->nextSiblings); // Duyệt anh em cùng cấp
    }

    //In thứ tự duyệt theo preOrder
    void printPreOrder() {
        preOrder(root);
        cout << endl;
    }

    // Duyệt cây theo postOrder
    void postOrder(Node* root) {
        if (root == nullptr) return;

        // Duyệt toàn bộ cây con trước
        postOrder(root->firstChild);

        // Sau khi duyệt hết con, in nút hiện tại
        cout << root->data << " ";

        // Duyệt tất cả anh em cùng cấp
        postOrder(root->nextSiblings);
    }

    //In thứ tự duyệt theo postOrder
    void printPostOrder() {
        postOrder(root);
        cout << endl;
    }

    // Hàm kiểm tra cây nhị phân
    bool isBinaryTree(Node* root) {
        if(root == nullptr){
            return true; // Cây rỗng là cây nhị phân
        }
        int count = 0; // Khởi tạo biến đếm

        Node* child = root->firstChild;

        while(child) {
            count++;
            if (count > 2){
                return false; // Nếu có hơn 2 con thì không phải cây nhị phân
            }
            if (!isBinaryTree(child)){
                return false; // Đệ quy kiểm tra cây con
            }
            child = child->nextSiblings;
        }
        return true;
    }

    bool checkBinaryTree() {
        return isBinaryTree(root);
    }

    // Duyệt theo Inorder nếu là cây nhị phân
    void inOrder(Node* root) {
        if(root == nullptr){
            return;
        }
        if(root->firstChild){
            inOrder(root->firstChild); // Duyệt con trái trước
        }
        cout << root->data << " "; // In dữ liệu nút hiện tại
        if(root->firstChild && root->firstChild->nextSiblings) // Nếu có con phải, duyệt con phải
            inOrder(root->firstChild->nextSiblings);
    }

    //In thứ tự duyệt theo inOrder
    void printInOrder() {
        if (checkBinaryTree()) {
            inOrder(root);
            cout << endl;
        } else {
            cout << "NOT BINARY TREE" << endl;
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m; // Nhập số nút và số cạnh

    Tree myTree;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        myTree.makeTree(x, y);
    }

    myTree.printHeight(); // In chiều cao của cây
    myTree.printPreOrder(); // In thứ tự duyệt preOrder
    myTree.printPostOrder(); // In thứ tự duyệt postOrder
    myTree.printInOrder(); // Kiểm tra và in inOrder nếu là cây nhị phân

    return 0;
}
