library(hutilscpp)
library(hutils)
library(tinytest)
olat <- seq(-10, -40, length.out = 1e5)
olon <- seq(114, 151, length.out = 1e5)

c_latlon <- compress_latlon(olat, olon)
expect_true(is.integer(c_latlon))
d_latlon <- decompress_latlon(c_latlon)
dist_ <- haversine_distance(olat, olon, d_latlon[[1]], d_latlon[[2]])
expect_true(max(dist_) < 0.15)

olat <- seq(-10, -40, length.out = 1e6)
olon <- seq(114, 151, length.out = 1e6)

c_latlon <- compress_latlon_general(olat, olon)
expect_true(is.integer(c_latlon))
d_latlon <- decompress_latlon_general(c_latlon)
dist_ <- haversine_distance(olat, olon, d_latlon[[1]], d_latlon[[2]])
expect_true(max(dist_) < 0.1)
