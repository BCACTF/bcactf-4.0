#[macro_use] extern crate nickel;

use nickel::{Nickel, HttpRouter, StaticFilesHandler, NickelError, Request, Response, MiddlewareResult};
use std::{fs::File, io::Read};

use std::collections::HashMap;

fn serve_page<'a>(_: &mut Request, res: Response<'a>) -> MiddlewareResult<'a> {
    let mut data = HashMap::<&str, &str>::new();

    data.insert("name", "Nickel");

    res.render("www/", &data)
}

fn main() {
    let mut server = Nickel::new();

    server.utilize(StaticFilesHandler::new("public/"));
    server.get("/login/*", tmpl_handler);

    // add a route
    server.get("/", middleware! { |_, res|
        // read the file
        let mut file = File::open("index.html").unwrap();
        // write the file to the response
        res.send(&mut file)
    });

    // add a route
    server.post("/times", middleware! { |req, res|
        //check the headers for the event type
        let event_type : str = req.origin.headers.get_raw("event-type").unwrap();
        // check the event type
        if event_type == "start" {
            // write the 'start_time' header to a new file with the name by the user id
            let user_id = req.origin.headers.get_raw("user-id").unwrap();
            let start_time = req.origin.headers.get_raw("start-time").unwrap();
            let mut file = File::create(user_id + ".txt").unwrap();
            file.write_all(start_time);
        } else if event_type == "stop" {
            //open the file with the user id
            let user_id = req.headers.get_raw("user-id").unwrap();
            let mut file = File::open(user_id + ".txt").unwrap();

            let start_time = String::new();
            file.read_to_string(&start_time);
            let stop_time = req.headers.get_raw("stop-time").unwrap();
            let time_diff = stop_time - start_time;
            
            if time_diff < 5 {
                let mut file = File::open("flag.txt").unwrap();
                res.send(&mut file)
            }
        }
    });

    server.utilize(router! {
        get "**" => |_req, _res| {
            "Hello world!"
        }
    });

    let _listening = server.listen("127.0.0.1:6767")
        .expect("Failed to launch server");
}