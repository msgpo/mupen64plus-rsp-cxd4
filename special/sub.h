void SUB(int rs, int rt, int rd, int unused_sa)
{
    unused_sa = 0;
    if (rd == 0)
    {
        message("SUB\nTried to overwrite $zero.", 1);
        return;
    }
    SR[rd] = SR[rs] - SR[rt];
    return;
}
