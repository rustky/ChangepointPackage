#' Binary Segmentation
#'
#' @param data.dt numeric data table of response variables[A x B]
#' @param Kmax int desired number of segments [N]
#'
#' @importFrom utils tail
#' @import data.table
#' @return Output list including the loss values at each split[1 x N]
#'
#' @export
BINSEG <- function(data.dt, Kmax){
  loss <- function(cum.sum.vec, cum.square.vec, N.data.vec){
    cum.square.vec-cum.sum.vec^2/N.data.vec
  }
  make.possible <- function(segs.dt){
    segs.dt[, data.table(
      first_seg_end=seq(first_seg_start, second_seg_end-1)
    ), by=.(first_seg_start, second_seg_end)]}
  data.dt[, cum.data := cumsum(logratio)]
  data.dt[, .(logratio, cum.data)]
  data.dt[, cum.square := cumsum(logratio^2)]
  fstart <- 1
  fend <- nrow(data.dt)
  output.list <- list()
  loss.vec <- loss(data.dt$cum.data, data.dt$cum.square,
                   1:nrow(data.dt))
  output.list[["1"]] = tail(loss.vec,n =1)
  for(K in 2:Kmax){
    (possible.dt <- data.table(
      first_seg_end = seq(fstart, (fend-1))))
    possible.dt[, first_seg_mean := {
      data.dt$cum.data[first_seg_end]/first_seg_end
    }]
    possible.dt[, first_seg_cum :=
                  data.dt[fstart:(fend-1), cum.data]]
    possible.dt[, first_seg_cum_sq:=
                  data.dt[fstart:(fend-1), cum.square]]
    possible.dt[, first_seg_loss := {
      possible.dt[
        first_seg_end,
        loss(first_seg_cum, first_seg_cum_sq, first_seg_end)]
    }]
    data.dt
    possible.dt[, cum.data.after := {
      data.dt[.N, cum.data]-possible.dt[first_seg_end, first_seg_cum]
    }]
    possible.dt[, cum.square.after := {
      data.dt[.N, cum.square]-
        possible.dt[first_seg_end, first_seg_cum_sq]
    }]
    possible.dt[, N.data.after := fend-first_seg_end]
    possible.dt[, second_seg_loss := {
      loss(cum.data.after, cum.square.after, N.data.after)
    }]
    possible.dt[order(second_seg_loss)]
    possible.dt[, split_loss := {
      first_seg_loss + second_seg_loss
    }]
    possible.dt[order(split_loss)]
    segs.after.first.split <- possible.dt[which.min(split_loss), rbind(
      data.table(first_seg_start=fstart, second_seg_end=first_seg_end),
      data.table(first_seg_start=first_seg_end+1, second_seg_end=fend)
    )]
    segs.before.first.split <- data.table(
      first_seg_start=fstart, second_seg_end=fend)
    make.possible(segs.before.first.split)
    (all.new.possible <- make.possible(segs.after.first.split))
    all.new.possible[, no_split:= possible.dt[fstart,split_loss]]
    all.new.possible[, loss_decrease := no_split -
                       possible.dt[1:.N-1,split_loss]]
    (min.idx <- all.new.possible[which.max(loss_decrease),first_seg_start])
    output.list[[paste(K)]] <- possible.dt[min.idx,split_loss]
    fstart <- min.idx
    fend <- segs.after.first.split[2,second_seg_end]
  }
  out.vec <- do.call(rbind,output.list)
  return(out.vec)
}
