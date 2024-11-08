using namespace std;

class request {
    std::string address;
    std::string response;

    public:
        request();
        request(string addr);
        static size_t handle_data(void* response, size_t size, size_t num_elements, void* userp);
        void make_request();
};