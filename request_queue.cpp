#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server)
        : search_server_(search_server) {
}

template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
    std::vector<Document> results = search_server_.FindTopDocuments(raw_query, document_predicate);

    QueryResult query_result;
    query_result.results_amount = results.size();
    query_result.current_time = 1;  // Set current_time to 1 for all requests
    requests_.push_back(query_result);
    if (requests_.size() > min_in_day_) {
        requests_.pop_front();
    }

    return results;
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    return AddFindRequest(
            raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
                return document_status == status;
            });
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    return AddFindRequest(raw_query, DocumentStatus::ACTUAL);
}

int RequestQueue::GetNoResultRequests() const {
    int no_result_requests = 0;
    for (QueryResult r : requests_) {
        if (r.results_amount == 0) {
            ++no_result_requests;
        }
    }
    return no_result_requests;
}