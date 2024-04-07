#include <sstream>
#include <thread>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <rapidjson/error/en.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include "api.h"

namespace mortido::net {

std::optional<rapidjson::Document> Api::universe() {
//  std::string a =R"(
//      {"name":"Test Team Please Ignore","roundName":"Trial 2","roundEndIn":292,"ship":{"fuelUsed":781,"planet":{"name":"Schiller","garbage":{}},"capacityX":8,"capacityY":11,"garbage":{}},"universe":[["Earth","Roob-43",96],["Earth","Kunde",73],["Earth","Block",78],["Roob-43","Earth",81],["Roob-43","Moen",44],["Roob-43","KDEKYVTB1",18],["Roob-43","BeautifulWoodchuck",78],["Kunde","Earth",74],["Kunde","King",49],["Kunde","CleanBee42",65],["Kunde","Klocko-72",22],["Block","Earth",54],["Block","B2N1JGPZ8",28],["Moen","Roob-43",4],["Moen","PinkMirror",37],["Moen","Wolff-238",38],["KDEKYVTB1","Daniel",99],["KDEKYVTB1","Hirthe-232",99],["KDEKYVTB1","McKenzie",66],["BeautifulWoodchuck","Roob-43",96],["BeautifulWoodchuck","Flatley",59],["BeautifulWoodchuck","FrighteningWheelchair",7],["King","Kunde",7],["King","McDermott",56],["King","Tromp",79],["King","Christiansen-247",69],["CleanBee42","U08Y4VWL2",97],["Klocko-72","Kunde",46],["Klocko-72","Schaefer",41],["Klocko-72","ElderberryZealous64",73],["Klocko-72","1GF23Y4C7",5],["B2N1JGPZ8","Block",79],["B2N1JGPZ8","Rosenbaum-83",51],["B2N1JGPZ8","Schiller",51],["PinkMirror","Moen",23],["PinkMirror","NicheTurtle75",66],["PinkMirror","Stark",3],["Wolff-238","Moen",19],["Wolff-238","TastyPug",41],["Wolff-238","Rogahn",37],["Daniel","KDEKYVTB1",22],["Daniel","ElderberryPrickling5",42],["Hirthe-232","Hirthe",38],["Hirthe-232","Botsford",62],["McKenzie","KDEKYVTB1",8],["McKenzie","ShinyChimpanzee917",67],["McKenzie","Q8DZ5T2F1",90],["McKenzie","DisturbedGuitar87",36],["Flatley","BeautifulWoodchuck",26],["Flatley","MU2ZD78V6",12],["Flatley","Renner-22",26],["FrighteningWheelchair","HostelFighter",82],["FrighteningWheelchair","Wiza",29],["FrighteningWheelchair","PCUJMF9A5",86],["McDermott","King",45],["McDermott","Murray-133",76],["Tromp","King",88],["Tromp","Kulas-262",17],["Tromp","DamsonColorful",16],["Christiansen-247","LRXB29ZE9",17],["Christiansen-247","HungryWasp",80],["Christiansen-247","ZOB41QG88",53],["U08Y4VWL2","CleanBee42",94],["U08Y4VWL2","5HCY18KL5",41],["U08Y4VWL2","Kihn-143",23],["Schaefer","Klocko-72",94],["Schaefer","Barrows-204",58],["Schaefer","Cummings-110",61],["Schaefer","JEI259730",81],["ElderberryZealous64","Klocko-72",7],["ElderberryZealous64","PlumDifficult492",83],["ElderberryZealous64","BowTalker0",6],["1GF23Y4C7","TZMLWFQO4",65],["1GF23Y4C7","Borer",79],["1GF23Y4C7","PanickedJackal",87],["Rosenbaum-83","B2N1JGPZ8",72],["Rosenbaum-83","CarefulSocks",34],["Rosenbaum-83","Hoeger-122",19],["Schiller","PJ7FJIPE6",111],["NicheTurtle75","PinkMirror",39],["NicheTurtle75","V2VPTYB55",95],["NicheTurtle75","Gaylord",45],["NicheTurtle75","WBE4R6F67",23],["Stark","Dach-15",52],["Stark","EUFJNBMO7",91],["Stark","6ELWXCTD0",29],["TastyPug","Wolff-238",17],["TastyPug","Jones-225",77],["Rogahn","Wolff-238",7],["Rogahn","FamousRestaurant7",27],["Rogahn","4HW5M3J37",72],["Rogahn","EL9T347N9",66],["ElderberryPrickling5","Daniel",17],["ElderberryPrickling5","Swift-279",19],["ElderberryPrickling5","Price-85",47],["Hirthe","Hirthe-232",52],["Hirthe","Feil-36",83],["Hirthe","Kassulke-254",97],["Botsford","GrapeRich42",92],["Botsford","Harvey-291",58],["ShinyChimpanzee917","McKenzie",99],["ShinyChimpanzee917","Ondricka-257",60],["ShinyChimpanzee917","Smith",84],["Q8DZ5T2F1","Hyatt-284",71],["DisturbedGuitar87","McKenzie",12],["DisturbedGuitar87","P61UV2PQ1",52],["DisturbedGuitar87","BlackcurrantOrange",17],["DisturbedGuitar87","Huel",40],["MU2ZD78V6","Flatley",98],["MU2ZD78V6","Rodriguez",75],["Renner-22","YoungRaven",25],["Renner-22","Schamberger",19],["HostelFighter","FrighteningWheelchair",71],["HostelFighter","Upton",57],["HostelFighter","Weimann-161",49],["HostelFighter","DamsonPlain",19],["Wiza","Gottlieb",27],["Wiza","Herzog-35",59],["PCUJMF9A5","BonesCooker6",5],["PCUJMF9A5","Feeney-256",39],["PCUJMF9A5","5LKOV4698",76],["Murray-133","McDermott",50],["Murray-133","Boehm",79],["Murray-133","Schoen",74],["Kulas-262","Tromp",69],["Kulas-262","Q2S9H0WH9",9],["Kulas-262","Donnelly",95],["DamsonColorful","Tromp",93],["DamsonColorful","Predovic",49],["DamsonColorful","Eden",54],["LRXB29ZE9","Christiansen-247",63],["LRXB29ZE9","HungryWasp",19],["HungryWasp","ZOB41QG88",77],["ZOB41QG88","PlumDifficult492",29],["5HCY18KL5","U08Y4VWL2",28],["5HCY18KL5","Kihn-143",44],["Kihn-143","V2VPTYB55",40],["Barrows-204","Schaefer",53],["Barrows-204","Cummings-110",2],["Cummings-110","JEI259730",48],["JEI259730","Schaefer",31],["PlumDifficult492","ElderberryZealous64",62],["PlumDifficult492","BowTalker0",45],["BowTalker0","Rosenbaum-83",25],["TZMLWFQO4","1GF23Y4C7",68],["TZMLWFQO4","Borer",53],["Borer","PanickedJackal",72],["PanickedJackal","TastyPug",99],["CarefulSocks","Rosenbaum-83",59],["CarefulSocks","Hoeger-122",44],["Hoeger-122","Wolff-238",55],["PJ7FJIPE6","Schiller",68],["PJ7FJIPE6","TastyPug",61],["V2VPTYB55","NicheTurtle75",20],["V2VPTYB55","Gaylord",62],["Gaylord","NicheTurtle75",35],["Gaylord","WBE4R6F67",20],["WBE4R6F67","NicheTurtle75",3],["Dach-15","Stark",66],["Dach-15","EUFJNBMO7",12],["EUFJNBMO7","Stark",41],["EUFJNBMO7","6ELWXCTD0",28],["6ELWXCTD0","Stark",44],["6ELWXCTD0","PlumDifficult492",40],["Jones-225","TastyPug",63],["FamousRestaurant7","Rogahn",15],["FamousRestaurant7","4HW5M3J37",20],["4HW5M3J37","Rogahn",58],["4HW5M3J37","EL9T347N9",67],["EL9T347N9","PinkMirror",86],["Swift-279","ElderberryPrickling5",39],["Swift-279","Price-85",57],["Price-85","ElderberryPrickling5",39],["Feil-36","Hirthe",24],["Feil-36","Kassulke-254",76],["Kassulke-254","Jones-225",17],["GrapeRich42","Botsford",82],["GrapeRich42","Harvey-291",89],["Harvey-291","Predovic",75],["Ondricka-257","ShinyChimpanzee917",24],["Ondricka-257","Smith",76],["Smith","Rodriguez",55],["Hyatt-284","Q8DZ5T2F1",77],["Hyatt-284","Murray-133",54],["P61UV2PQ1","DisturbedGuitar87",7],["P61UV2PQ1","BlackcurrantOrange",32],["BlackcurrantOrange","DisturbedGuitar87",32],["BlackcurrantOrange","Huel",21],["Huel","Moen",36],["Rodriguez","MU2ZD78V6",48],["YoungRaven","Renner-22",6],["YoungRaven","Schamberger",8],["Schamberger","B2N1JGPZ8",85],["Upton","HostelFighter",44],["Upton","Weimann-161",7],["Weimann-161","HostelFighter",8],["Weimann-161","DamsonPlain",30],["DamsonPlain","Kulas-262",59],["Gottlieb","Wiza",60],["Gottlieb","Herzog-35",67],["Herzog-35","Murray-133",31],["BonesCooker6","PCUJMF9A5",47],["BonesCooker6","Feeney-256",75],["Feeney-256","5LKOV4698",72],["5LKOV4698","JEI259730",66],["Boehm","Murray-133",57],["Boehm","Schoen",20],["Schoen","PinkMirror",87],["Q2S9H0WH9","Kulas-262",7],["Q2S9H0WH9","Donnelly",8],["Donnelly","Kulas-262",32],["Predovic","DamsonColorful",86],["Predovic","Eden",77],["Eden","DamsonColorful",88]],"attempt":1}
//  )";
//  return parse_json(a);
  return parse_json(get(server_url_ + "/player/universe"));
}

std::optional<rapidjson::Document> Api::rounds() {
  return parse_json(get(server_url_ + "/player/rounds"));
}

std::optional<std::string> Api::get_current_round() {
  auto doc = rounds();

  if (!doc) {
    return std::nullopt;
  }

  if (doc->HasMember("rounds") && (*doc)["rounds"].IsArray()) {
    for (const auto &round : (*doc)["rounds"].GetArray()) {
      if (round["isCurrent"].GetBool()) {
        return round["name"].GetString();
      }
    }
  }
  return std::nullopt;
}

std::optional<rapidjson::Document> Api::travel(const std::vector<std::string> &planets) {
//  std::string a =R"(
//  {"planetGarbage":{"2JwFhC":[[0,3],[0,2],[0,1],[0,0],[1,1],[2,1],[2,0]],"2LNYyK":[[0,3],[0,2],[0,1],[0,0],[1,3],[2,3],[2,2],[2,1],[2,0],[3,2],[3,0]],"2LNt9c":[[0,2],[1,2],[1,1],[1,0],[2,2],[3,2]],"2LPDnQ":[[0,2],[1,2],[1,1],[1,0],[2,1],[3,1],[3,0]],"2LPZ2w":[[0,0],[1,0],[1,1],[1,2],[2,2]],"2LPtfj":[[0,0],[1,0],[2,0],[2,1],[2,2]],"2LQZwK":[[0,3],[0,2],[0,1],[1,3],[1,1],[2,3],[2,1],[2,0]],"2LREHu":[[0,3],[0,2],[0,1],[0,0],[1,3],[1,1],[2,3],[2,1],[2,0]],"2LREkQ":[[0,3],[0,2],[0,1],[0,0],[1,3],[1,0],[2,3],[2,2],[2,0]],"6YyTaBS":[[0,0],[1,0],[2,0],[0,1],[0,2],[1,2],[1,3]],"6YyUEzX":[[0,0],[1,0],[2,0],[3,0]],"6YyUFT2":[[0,2],[0,1],[0,0],[1,1],[2,1],[3,1],[3,0]],"6YzuD6M":[[0,1],[0,0],[1,1],[2,1]],"6YzuYGe":[[0,2],[0,1],[0,0],[1,1]],"6YzusuS":[[0,3],[0,2],[0,1],[0,0],[1,1],[2,1],[2,0]],"6YzvD9y":[[0,3],[0,2],[0,1],[1,3],[2,3],[2,2],[2,1],[3,1],[3,0]],"6YzvYnm":[[0,0],[1,0],[2,0],[3,0],[0,1],[3,1],[0,2],[1,2]],"6YzwDbr":[[0,3],[0,2],[0,1],[0,0],[1,3],[1,0],[2,3],[2,2],[3,3]],"6YzxEaU":[[0,2],[0,1],[1,1],[1,0]],"6tXakmC":[[0,2],[0,1],[0,0],[1,1]],"6tXb5wV":[[0,0],[0,1],[1,1],[2,1],[0,2]],"6tXb6Pz":[[0,0],[1,0],[1,1],[1,2]],"6tXbReX":[[0,0],[1,0],[2,0],[2,1],[2,2]],"6tXbS72":[[0,0],[1,0],[2,0]],"6tXbmHK":[[0,0],[0,1],[1,1],[1,2]],"6tXc6Tc":[[0,0],[0,1],[1,1],[2,1],[3,1],[0,2],[3,2],[0,3]],"6tXc6v7":[[0,0],[1,0],[2,0],[0,1],[0,2],[1,2],[2,2],[3,2],[1,3],[3,3]],"6tXcS6Q":[[0,0],[1,0],[2,0],[3,0],[1,1],[3,1],[1,2],[1,3],[2,3]],"6tXcSYu":[[0,3],[0,2],[0,1],[1,2],[2,2],[2,1],[2,0],[3,2],[3,0]],"6tXcmjC":[[0,0],[1,0]],"6tZ3jNX":[[0,3],[0,2],[0,1],[0,0],[1,2],[2,2],[2,1],[2,0]],"6tZ3jq2":[[0,0],[0,1],[1,1],[2,1],[3,1],[0,2],[3,2],[0,3],[3,3]],"6tZ455Z":[[0,3],[0,2],[0,1],[1,3],[1,1],[1,0],[2,3],[2,0],[3,3]],"6tZ4QFr":[[0,2],[1,2],[1,1],[2,1],[2,0],[3,1]],"6tZ4QiM":[[0,3],[1,3],[1,2],[1,1],[1,0],[2,3]],"6tZ4jte":[[0,3],[0,2],[0,1],[1,1],[1,0],[2,1],[3,1],[3,0]],"6tZ4kM9":[[0,2],[0,1],[1,1],[1,0]],"6tZ55XS":[[0,0],[1,0],[2,0],[0,1],[0,2],[1,2],[2,2],[1,3]],"6tZ5Qhj":[[0,3],[1,3],[1,2],[1,1],[1,0],[2,3],[2,0],[3,0]],"6tZ5RAE":[[0,2],[1,2],[1,1],[1,0],[2,0]],"6tZ5kLX":[[0,0],[1,0],[2,0],[2,1],[2,2]],"6tZ5ko2":[[0,0],[1,0],[2,0],[1,1],[2,1],[3,1]],"6tZ663Z":[[0,0],[1,0],[2,0],[0,1],[2,1],[3,1]],"6tZ6RDr":[[0,0],[1,0],[2,0]],"6tZ6RgM":[[0,0],[0,1],[1,1],[0,2],[1,2],[0,3]],"6tZ6kre":[[0,0],[1,0],[2,0],[0,1],[2,1],[3,1],[0,2],[2,2],[0,3]],"6tZ6mK9":[[0,3],[1,3],[1,2],[1,1],[1,0],[2,3],[3,3]],"7TNer3A":[[0,3],[0,2],[0,1],[0,0],[1,3],[2,3],[2,2],[2,1],[3,1],[3,0]],"7TNfBHh":[[0,0],[1,0],[2,0],[3,0],[0,1],[3,1],[0,2],[3,2],[0,3],[1,3]],"7TNfBkC":[[0,3],[0,2],[0,1],[1,2],[2,2],[2,1],[2,0],[3,2]],"7TNfWvV":[[0,2],[0,1],[1,2],[2,2],[2,1],[2,0],[3,1]],"7TNfr6n":[[0,0],[0,1],[1,1],[1,2]],"7TNfrZH":[[0,0],[0,1],[1,1],[2,1],[3,1],[1,2],[3,2],[1,3],[3,3]],"7TNgBja":[[0,0],[1,0],[2,0],[3,0],[1,1],[3,1],[1,2]],"7TNgCC5":[[0,3],[0,2],[0,1],[1,3],[2,3],[2,2],[2,1],[3,1],[3,0]],"7TNgXNN":[[0,0],[1,0],[0,1],[0,2],[1,2],[2,2],[0,3],[2,3],[3,3]],"7TNgrYf":[[0,2],[0,1],[0,0],[1,1]],"7TNgs1A":[[0,2],[0,1],[1,1],[1,0],[2,1]],"7TQ7pij":[[0,3],[0,2],[0,1],[1,3],[1,1],[2,3],[2,1],[2,0],[3,3],[3,0]],"7TQ89u2":[[0,0],[1,0],[2,0],[0,1],[2,1],[3,1],[0,2],[2,2]],"7TQ8AMX":[[0,0],[0,1],[1,1],[2,1],[3,1],[0,2],[0,3],[1,3],[2,3]],"7TQ8VXp":[[0,0],[0,1],[0,2],[1,2],[2,2],[3,2],[3,3]],"7TQ8VzK":[[0,0],[0,1],[1,1],[2,1],[3,1],[1,2]],"7TQ8qAc":[[0,0],[1,0],[2,0],[0,1],[2,1],[0,2]],"7TQ9ALu":[[0,3],[1,3],[1,2],[1,1],[1,0],[2,3],[2,0],[3,3],[3,2],[3,0]],"7TQ9AoQ":[[0,2],[0,1],[1,1],[1,0]],"7TQ9Vyh":[[0,0],[1,0],[2,0],[0,1],[0,2],[0,3]],"7TQ9WSC":[[0,2],[0,1],[0,0],[1,1]],"7TQ9qgj":[[0,0],[0,1],[1,1],[0,2],[0,3],[1,3],[2,3]],"7TQAAs2":[[0,0],[0,1],[1,1],[2,1],[3,1],[1,2],[3,2],[3,3]],"7TQABKX":[[0,0],[1,0]],"7TQAWVp":[[0,0],[1,0],[1,1],[1,2]]},"shipGarbage":null,"fuelDiff":51,"planetDiffs":[{"from":"Schiller","to":"PJ7FJIPE6","fuel":61}]}
//  )";
//  return parse_json(a);
  rapidjson::Document doc;
  doc.SetObject();
  rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
  rapidjson::Value planets_array(rapidjson::kArrayType);
  for (const auto &planet : planets) {
    rapidjson::Value planet_value;
    planet_value.SetString(planet.c_str(), static_cast<rapidjson::SizeType>(planet.length()), allocator);
    planets_array.PushBack(planet_value, allocator);
  }

  doc.AddMember("planets", planets_array, allocator);
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  doc.Accept(writer);
  return parse_json(post(server_url_ + "/player/travel", buffer.GetString()));
}

std::optional<rapidjson::Document> Api::collect(const std::vector<models::Garbage> &garbage) {
  rapidjson::Document doc;
  doc.SetObject();
  rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();

  rapidjson::Value garbageObject(rapidjson::kObjectType);
  for (const auto &g : garbage) {
    rapidjson::Value key(g.name.c_str(), allocator);
    rapidjson::Value points(rapidjson::kArrayType);
    for (const auto &point : g.points) {
      rapidjson::Value point_value(rapidjson::kArrayType);
      point_value.PushBack(point.x, allocator);
      point_value.PushBack(point.y, allocator);
      points.PushBack(point_value, allocator);
    }
    garbageObject.AddMember(key, points, allocator);
  }

  doc.AddMember("garbage", garbageObject, allocator);
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  doc.Accept(writer);
  return parse_json(post(server_url_ + "/player/collect", buffer.GetString()));
}

std::optional<rapidjson::Document> Api::reset() {
  return parse_json(delete_method(server_url_ + "/player/reset"));
}

std::optional<std::string> Api::perform_request(const std::string &url,
                                                const std::string &method,
                                                const std::string &body) {
  LOG_INFO("Request to %s", url.c_str());
  for (int attempt = 0; attempt < max_retries_; ++attempt) {
    ensure_rate_limit();

    try {
      std::ostringstream response_stream;
      curlpp::Easy request;
      request.setOpt<curlpp::options::Url>(url);
      request.setOpt<curlpp::options::HttpHeader>(headers_);
      request.setOpt<curlpp::options::WriteStream>(&response_stream);

      if (method == "POST") {
        request.setOpt<curlpp::options::PostFields>(body);
        request.setOpt<curlpp::options::PostFieldSize>(body.length());
      } else if (method == "DELETE" && !body.empty()) {
        request.setOpt<curlpp::options::CustomRequest>("DELETE");
        if (!body.empty()) {
          request.setOpt<curlpp::options::PostFields>(body);
          request.setOpt<curlpp::options::PostFieldSize>(body.length());
        }
      }
      request.perform();
      auto result = response_stream.str();
      LOG_INFO("Request to '%s' with data='%s' result='%s'", url.c_str(), body.c_str(), result.c_str());
      return result;
    } catch (curlpp::RuntimeError &e) {
      LOG_WARN("Runtime error on request to %s attempt %d: %s", url.c_str(), attempt + 1, e.what());
    } catch (curlpp::LogicError &e) {
      LOG_WARN("Logic error on request to %s attempt %d: %s", url.c_str(), attempt + 1, e.what());
    }
  }

  LOG_ERROR("Request was not executed %s", url.c_str());
  return std::nullopt;
}

std::optional<rapidjson::Document> Api::parse_json(const std::optional<std::string> &json_string) {
  if (!json_string.has_value()) {
    return std::nullopt;
  }

  rapidjson::Document document;
  rapidjson::ParseResult result = document.Parse(json_string.value().c_str());
  if (!result) { // Equivalent to HasParseError()
    LOG_ERROR("JSON parse error: %s, offset: %zu",
              rapidjson::GetParseError_En(result.Code()),
              result.Offset());
    return std::nullopt;
  }

  if (document.HasMember("error") && document["error"].IsString()) {
    LOG_ERROR("Request returned error: %s", document["error"].GetString());
    return std::nullopt;
  }
  return document;
}

void Api::ensure_rate_limit() {
  if (request_times_.size() < max_rpc_) {
    return;
  }

  auto now = std::chrono::steady_clock::now();
  auto oldest_request = request_times_.front();
  auto time_since_oldest_request = duration_cast<std::chrono::milliseconds>(now - oldest_request);

  if (time_since_oldest_request < std::chrono::seconds(1)) {
    auto delay_time = std::chrono::seconds(1) - time_since_oldest_request;
    std::this_thread::sleep_for(delay_time);
  }

  request_times_.push(std::chrono::steady_clock::now());
  request_times_.pop();
}

}
