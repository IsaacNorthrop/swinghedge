using namespace std;

class request {
    std::string address;

    public:
        std::string response;
        request();
        request(string addr);
        static size_t handle_data(void* response, size_t size, size_t num_elements, void* userp);
        void make_request();
};