use std::panic::Location;

use axum::async_trait;
use axum::extract::FromRequestParts;
use axum::http::request::Parts;
use axum::response::{IntoResponse, Response};

use crate::http::axum_implementation::query::Query;
use crate::http::axum_implementation::requests::scrape::{ParseScrapeQueryError, Scrape};
use crate::http::axum_implementation::responses;

pub struct ExtractRequest(pub Scrape);

#[async_trait]
impl<S> FromRequestParts<S> for ExtractRequest
where
    S: Send + Sync,
{
    type Rejection = Response;

    async fn from_request_parts(parts: &mut Parts, _state: &S) -> Result<Self, Self::Rejection> {
        let raw_query = parts.uri.query();

        if raw_query.is_none() {
            return Err(responses::error::Error::from(ParseScrapeQueryError::MissingParams {
                location: Location::caller(),
            })
            .into_response());
        }

        let query = raw_query.unwrap().parse::<Query>();

        if let Err(error) = query {
            return Err(responses::error::Error::from(error).into_response());
        }

        let scrape_request = Scrape::try_from(query.unwrap());

        if let Err(error) = scrape_request {
            return Err(responses::error::Error::from(error).into_response());
        }

        Ok(ExtractRequest(scrape_request.unwrap()))
    }
}