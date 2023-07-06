void run(){

    /**
     * description 求多叉树任意两点的最近公共父节点
     * @author oswin
     * @date 2023/07/06
     *          １
     *       ／ |  \
     *     2 3(5) 4(4)
     *         /\
     *     (5)5  6(null)
     * fun(root,5,4)返回1: 父节点３，left(５)返回５，right(６)返回null,
     * (left!=null and right!=null)->root; 一个为空,另一个存在->some(left,right)
     */

    struct node{
        explicit node(int id):idx(id){}
        vector<shared_ptr<node>>sons;
        int idx{0};;
    };

    shared_ptr<node>n1(new node(1));
    shared_ptr<node>n2(new node(2));
    shared_ptr<node>n3(new node(3));
    shared_ptr<node>n4(new node(4));
    shared_ptr<node>n5(new node(5));
    shared_ptr<node>n6(new node(6));
    shared_ptr<node>n7(new node(7));

    n1->sons.emplace_back(n2);
    n1->sons.emplace_back(n3);
    n1->sons.emplace_back(n4);
    n3->sons.emplace_back(n5);
    n3->sons.emplace_back(n6);
    n4->sons.emplace_back(n7);

    function<shared_ptr<node>(shared_ptr<node> root, int p, int q)> func = [&](const shared_ptr<node> &root, int p,
                                                                               int q) -> shared_ptr<node> {
        if (root->idx == p or root->idx == q) return root;
        if (root->sons.empty()) return nullptr;

        int rightId{INT_MAX};
        shared_ptr<node> left, right;

        for (int i = 0; i < (int) root->sons.size(); ++i) {
            left = func(root->sons[i], p, q);
            if (left) {
                rightId = i + 1;
                break;
            }
        }

        for (int i = rightId; i < (int) root->sons.size(); ++i) {
            right = func(root->sons[i], p, q);
            if (right) break;
        }

        if (left != nullptr and right != nullptr) return root;
        return (left ? left : right);
    };

    auto lca = func(n1,5,6);

    cout<<"lower common ancester: "<<lca->idx<<endl;
}
