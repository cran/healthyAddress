% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/extract_postcode.R
\name{extract_postcode}
\alias{extract_postcode}
\title{Extract the postcode from the suffix of a string}
\usage{
extract_postcode(x)
}
\arguments{
\item{x}{A character vector.}
}
\value{
An integer vector the same length as \code{x}, giving the
postcode as it appears in the last 3 or 4 characters in each
string. Returns \code{NA_integer_} for other strings.

There is no guarantee made that the postcode is a real postcode.
}
\description{
Extract the postcode from the suffix of a string
}
\examples{
extract_postcode("3000")
extract_postcode("Melbourne Vic 3000")

}
