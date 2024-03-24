<<<<<<< HEAD
#include "document.h"

std::ostream& operator<<(std::ostream& out, const Document& document) {
   out << "{ document_id = " << document.id << ", relevance = "
       << document.relevance << ", rating = " << document.rating <<" }";
   return out;
}
=======
//#include "document.h"
//
//std::ostream& operator<<(std::ostream& out, const Document& document) {
//    out << "{ document_id = " << document.id << ", relevance = "
//        << document.relevance << ", rating = " << document.rating <<" }";
//    return out;
//}
>>>>>>> 883db122232dd2c69aa36b90a7ccc9e492a0d80b
