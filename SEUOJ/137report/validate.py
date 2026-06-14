#!/usr/bin/env python3
# 校验 137 输出是否合法，并报告所选箱子体积
import sys, subprocess, random, os

def gen(n_items=12, m_boxes=5, seed=0):
    rnd = random.Random(seed)
    boxes = []
    for _ in range(m_boxes):
        boxes.append((rnd.randint(30,100), rnd.randint(30,100), rnd.randint(30,100)))
    items = []
    for _ in range(n_items):
        items.append((rnd.randint(5,40), rnd.randint(5,40), rnd.randint(5,40), rnd.randint(0,1)))
    lines = [f"{m_boxes} {n_items}"]
    for b in boxes: lines.append(f"{b[0]} {b[1]} {b[2]}")
    for it in items: lines.append(f"{it[0]} {it[1]} {it[2]} {it[3]}")
    return "\n".join(lines)+"\n", boxes, items

def rotations(it):
    l,w,h,rot = it
    res = [(l,w,h)]
    if l!=w: res.append((w,l,h))
    if rot==1:
        res += [(w,h,l),(h,w,l),(l,h,w),(h,l,w)]
    return res

def validate(inp, out, boxes, items):
    toks = out.split()
    if not toks: return False, "empty output"
    if toks[0] == "DORAYAKI": return True, "DORAYAKI"
    bid = int(toks[0])
    box = boxes[bid-1]
    nums = list(map(int, toks[1:]))
    n = len(items)
    if len(nums) != 6*n: return False, f"expected {6*n} nums, got {len(nums)}"
    placed = []
    for i in range(n):
        px,py,pz,sl,sw,sh = nums[6*i:6*i+6]
        # 尺寸必须是该道具某个合法旋转
        if (sl,sw,sh) not in rotations(items[i]):
            return False, f"item {i+1}: illegal rotation {(sl,sw,sh)}"
        # 越界
        if px<0 or py<0 or pz<0 or px+sl>box[0] or py+sw>box[1] or pz+sh>box[2]:
            return False, f"item {i+1}: out of box {box} at {(px,py,pz,sl,sw,sh)}"
        placed.append((px,py,pz,sl,sw,sh))
    # 两两不重叠
    for i in range(n):
        for j in range(i+1,n):
            a,b=placed[i],placed[j]
            dx = a[0]+a[3]<=b[0] or b[0]+b[3]<=a[0]
            dy = a[1]+a[4]<=b[1] or b[1]+b[4]<=a[1]
            dz = a[2]+a[5]<=b[2] or b[2]+b[5]<=a[2]
            if not(dx or dy or dz):
                return False, f"overlap items {i+1},{j+1}"
    return True, box[0]*box[1]*box[2]

if __name__ == "__main__":
    exe = sys.argv[1]
    seeds = range(int(sys.argv[2]) if len(sys.argv)>2 else 30)
    fails=0; vols=[]
    for s in seeds:
        inp, boxes, items = gen(seed=s)
        r = subprocess.run([exe], input=inp, capture_output=True, text=True, timeout=30)
        ok, info = validate(inp, r.stdout, boxes, items)
        if not ok:
            fails+=1; print(f"seed {s}: FAIL {info}")
        else:
            if info!="DORAYAKI": vols.append(info)
            print(f"seed {s}: OK vol={info}")
    print(f"\n{exe}: fails={fails}  total_vol={sum(v for v in vols)}")
